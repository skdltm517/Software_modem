typedef enum{
	normal,
	failed,
}End_reason;

typedef enum{
	halsrch_on,
	halsrch_off
}NHAL_state;

int NHAL_RFcmd_on();

int NHAL_srchcmd_on();

int sendResUpper();

int sendFailUpper();

int NHAL_RFcmd_off();
