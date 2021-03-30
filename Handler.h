
typedef enum{
	Idle,
	RF_on,
	Srch_on,
	RF_off,
	RF_sync,
	Nstate
}Scheduler_state;

typedef enum{
	EVT_GET_MSG,
	EVT_RFON_OK,
	EVT_RFOFF_OK,
	EVT_SRCH_FOFF,
	EVT_SRCH_NOFF,
	Nevent
}Scheduler_event;

Scheduler_state GetMsgHandler(int UE);

Scheduler_state RfOnHandler(int UE);

Scheduler_state SrchForceOffHandler(int UE);

Scheduler_state SrchNormalOffHandler(int UE);

Scheduler_state RfOffHandler(int UE);





