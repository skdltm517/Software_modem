#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef enum{
	Idle,
	vRFon,
	vSrchon,
	CellSearch,
	Srchfail,
	vRFsync
} Scheduler_state;



int main(void) {
	int exit = 0;
	Scheduler_state state = Idle;

	while(exit == 0){
		
		switch(state){
			case Idle :
				NHAL_RFcmd_on();
				state = vRFon;
				break;
				
			case vRFon :
				//nhal rf on 확인되면 
				NHAL_srchcmd_on();
				state = vSrchon;
				break;	
					 
			case vSrchon :
				//nhal srch on 확인되면
				state = CellSearch;
				break;
				
			case CellSearch:
				if (srchstate==srchst_off){
					state = Srchfail;
					break;
					
				}else{
					crccheck == ok;
					state = vRFsync;
					break;
				}
				
			case Srchfail:
				NHAL_RFcmd_off();
				state = Idle;
				break;
				
			case vRFsync:
				//대기하나 계속 에러날때까지?
				while(state != Srchfail){
					if (srchstate==srchst_off){
						state = Srchfail; 
					}else{
						//대기 
						usleep(1000); 
					}
				}
			default:
				exit = 1;
				printf("state error!");
				break;
			
		}
		
		
	}	
	
	
	
	
	return 0;
}
