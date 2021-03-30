#include <stdio.h>
#include <stdlib.h>
#include "NHAL_function.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct{
	int msgN;
	int cfg;
	void *next;
	
}Search_msg;

typedef enum{
	Idle,
	RF_on,
	Srch_on,
	RF_sync
}Scheduler_state;

typedef enum{
	normal_off,
	forced_off
}Srchoff_state;

int main(void) {
	int exit = 0;
	Scheduler_state state = Idle;
	Srchoff_state srchst;
	Search_msg *srch_msg;
	int secondsrch;
	
	while(exit == 0){
		
		switch(state){
			//IDLE = 아무것도 안하고 있는 상태
			// RRC command가 들어오면(event triggered) RFon 명령을 하고 RFon상태로 넘어감 
			case Idle :
				if(srch_msg != NULL){
					if(0 == NHAL_RFcmd_on()){	
						state = RF_on;
						break;
					}
					else{
						printf("RFon failed!");
						break;				
					}
						
				}
				state = Idle; 
				break;
				
			//RF_on = vRF가 켜지는  상태
			// RRC on이 성공하면 Srch on 명령을 하고 Srchon상태로 넘어감 				
			case RF_on :
					NHAL_srchcmd_on();
					state = Srch_on;
					break;	
					
			//Srch_on = vSrcher가 돌고있는 상태  
			//vSearcher가 정상 off 한 경우(event triggered) 셀을 찾았다고 판단하여 보고 후 RF_sync상태로 넘어감 
			//vSearcher가 비정상 off 한 경우(event triggered) 서치 실패로 판단하여 보고 후 RF off 하고 Idle상태로 넘어감 -> RF off 상태도 있어야되나? 
			case Srch_on :
				if(srchst == normal_off){
					sendResUpper();
					state = RF_sync;
					break;
				}else if(srchst == forced_off ){
					sendFailUpper();
					state = Idle;
					break;
				}
				state = Srch_on;
				break;	
					
			//RF_sync = vSrcher가 찾아낸 가장 최근의 timing을 RF가 잡고있는 상태 
			//새로운 정보의 RRC command가 들어오면(event triggered) RF off 명령을 하고 Idle상태로 넘어감
			//현재 정보와 일치하는 RRC command가 들어오면(event triggered) Srch on 명령을 하고 Srchon상태로 넘어감				
			case RF_sync:  
	
				if (srch_msg != NULL){
					//if(Search_msg.cfg.freq_offset == RF.freq_offset) 
					if( secondsrch == 1)
					{
						NHAL_srchcmd_on();
						state = Srch_on;
						break; 
					}else{
						NHAL_RFcmd_off();
						state = Idle;
						break;
					} 	
				}
				state = RF_sync;
				break;
				
			default:
				exit = 1;
				printf("wrong state error! (val : %s)\n",state);
				break;
			
		}
			
	}	
	
	return 0;
}
