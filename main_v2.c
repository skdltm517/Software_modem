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
			//IDLE = �ƹ��͵� ���ϰ� �ִ� ����
			// RRC command�� ������(event triggered) RFon ����� �ϰ� RFon���·� �Ѿ 
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
				
			//RF_on = vRF�� ������  ����
			// RRC on�� �����ϸ� Srch on ����� �ϰ� Srchon���·� �Ѿ 				
			case RF_on :
					NHAL_srchcmd_on();
					state = Srch_on;
					break;	
					
			//Srch_on = vSrcher�� �����ִ� ����  
			//vSearcher�� ���� off �� ���(event triggered) ���� ã�Ҵٰ� �Ǵ��Ͽ� ���� �� RF_sync���·� �Ѿ 
			//vSearcher�� ������ off �� ���(event triggered) ��ġ ���з� �Ǵ��Ͽ� ���� �� RF off �ϰ� Idle���·� �Ѿ -> RF off ���µ� �־�ߵǳ�? 
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
					
			//RF_sync = vSrcher�� ã�Ƴ� ���� �ֱ��� timing�� RF�� ����ִ� ���� 
			//���ο� ������ RRC command�� ������(event triggered) RF off ����� �ϰ� Idle���·� �Ѿ
			//���� ������ ��ġ�ϴ� RRC command�� ������(event triggered) Srch on ����� �ϰ� Srchon���·� �Ѿ				
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
