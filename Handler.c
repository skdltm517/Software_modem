//
#include <stdio.h>
#include <stdlib.h>
#include "Handler.h"

Scheduler_state GetMsgHandler(int UE)
{
	int arfcn, cfg;
	
	get_Message(&cfg,&arfcn);
	
	if(0 == NHAL_RFcmd_on(arfcn))
	{
		printf("\n[RF_on]\n");
		return RF_on;
	}		
	else
		printf("RFon failed!\n");	
	
	printf("\n[Idle]\n");
	return Idle;	
}

Scheduler_state RfOnHandler(int UE)
{	
	if(0==NHAL_srchcmd_on(UE))
	{
		printf("\n[Srch_on]\n");
		return Srch_on;
	}
}

Scheduler_state SrchForceOffHandler(int UE)
{	
	sendFailUpper();
	
	if(0 == NHAL_RFcmd_off())
	{
		printf("\n[RF_off]\n");
		return RF_off;	
	}
	else
		printf("RFon failed!");	

	printf("\n[Idle]\n");
	return Idle;
}

Scheduler_state SrchNormalOffHandler(int UE)
{
	sendResUpper(UE);
	printf("\n[RF_sync]\n");
	return RF_sync;
}

Scheduler_state RfOffHandler(int UE)
{
	printf("\n[Idle]\n");
	return Idle;		
}
