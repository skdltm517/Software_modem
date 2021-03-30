#include <stdio.h>
#include <stdlib.h>
#include "NHAL_function.h"

NHAL_state nhalonoff;
End_reason offreas;

int NHAL_RFcmd_on(int arfcn)
{
	
	printf("RF is turning on ..\n");
	sleep(3);
	
	printf("RF on! (arfcn = %d)\n",arfcn);
	
	return 0;
}


int NHAL_srchcmd_on()
{
	
	printf("Srcher is turning on ..\n");
	sleep(3);
	
	printf("Srcher on! (arfcn = %d)\n");
	nhalonoff = halsrch_on;
	
	sleep(2);
	
	printf("CRC check OK! \n ");
	
	printf("Srcher is turning off ..\n");
	sleep(3);
	
	printf("Srcher off! (arfcn = %d)\n");
	nhalonoff = halsrch_off;
	
	offreas = normal;
	return 0;	
}

int sendResUpper()
{
	sleep(1);

	printf("Sent result to Upper layer successfully! \n ");

	return 0;
}

int sendFailUpper()
{
	sleep(1);
	
	printf("Reported failed to Upper layer. \n ");
	
	return 0;
}

int NHAL_RFcmd_off(void)
{
	
	printf("RF is turning off ..\n");
	sleep(3);
	
	printf("RF normally off!\n");
	
	return 0;
}
