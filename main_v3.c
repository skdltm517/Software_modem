#include <stdio.h>
#include <stdlib.h>
#include "NHAL_function.h"
#include "Handler.h"

extern NHAL_state nhalonoff;
extern End_reason offreas;

typedef struct{
	int msgN;
	int arfcn; 
	int cfg;
	void *next;
}Search_msg;

Search_msg *srch_msg; 
typedef Scheduler_state (*const DoNext[Nstate][Nevent])(int UE);
//typedef Scheduler_state (*EvtHandler)(int UE);

void tmp_makeMSG(void)
{
	srch_msg = malloc(sizeof(Search_msg));
	srch_msg->msgN = 1;
	srch_msg->arfcn = 10;
	srch_msg->cfg = 123;
	srch_msg->next = NULL;
}
	
int get_Message(int *config, int *arfcn)
{
	int MSG;
	
	MSG = srch_msg->msgN;
	*arfcn = srch_msg->arfcn;
	*config = srch_msg->cfg;
	
	if(srch_msg->next != NULL)
		srch_msg = srch_msg->next;
	else
		free(srch_msg);
	
	return MSG;
}

Scheduler_event ReadEvent(Scheduler_state state)
{
	int exit = 0;	
	tmp_makeMSG();
	
	while(exit == 0)
	{
		switch(state)
		{		
			case Idle :
				if(srch_msg != NULL)
				{	
					return EVT_GET_MSG;
				}
				break;
			
			case RF_on :
				return EVT_RFON_OK;
				
			case Srch_on :
				if(nhalonoff == halsrch_off){
					if(offreas == normal)
						return EVT_SRCH_NOFF;
					else
						return EVT_SRCH_FOFF;
				}
				break;	
			
			case RF_off :				
				return EVT_RFOFF_OK;
					
			case RF_sync :
				if(srch_msg != NULL)
				{	
					return EVT_GET_MSG;
				}
				break;
		
			default :
				exit = 1;
				printf("wrong state error! (val : %s)\n",state);
				return -1;		
		}
		
	}
	
	printf("event trigger error!\n");
	return -1;
}

const static DoNext StateMachine =
{
	{GetMsgHandler, NULL, NULL, NULL, NULL},
	{NULL, RfOnHandler, NULL, NULL, NULL},
	{NULL, NULL, NULL, SrchForceOffHandler, SrchNormalOffHandler},
	{NULL, NULL, RfOffHandler, NULL, NULL},
	{GetMsgHandler, NULL, NULL, NULL, NULL}
};

int main(void) {
	int exit = 0;
	Scheduler_state NextState = Idle;
	Scheduler_event NewEvent;
	int UE;
	
	printf("\n[Idle]\n"); //starting state is IDLE
	
	while(1)
	{
		NewEvent = ReadEvent(NextState);
	
		if((NextState < Nstate) && 
			(NewEvent < Nevent) &&
			 StateMachine[NextState][NewEvent]!= NULL)
		{
			NextState = (*StateMachine[NextState][NewEvent])(UE);
		}else
		{
			printf("Failed State Machine!!(state : %d , event : %d)(max %d/%d)\n",
			NextState, NewEvent, Nstate-1, Nevent-1);
			break;
		}			
	
	}	
	
	return 0;
}
