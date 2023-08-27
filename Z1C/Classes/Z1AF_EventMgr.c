#include "Z1AF.h"
#include "Z1Adb.h"
#include "Z1CV.h"


ZBOOL ZafGetBasicEvent()
{
	ZBOOL nRet = ZFALSE;
	const int cnMaxLenBasicEvent = 2;
	const char* cszparrBasicEvent[2] =
	{
		"ONCLICK_CloseConfirmation",
		"ONCLICK_CloseNotify",
	};

	nRet = ZdDoBasicEvent(cszparrBasicEvent, cnMaxLenBasicEvent);
	Z1_PROCESS_ERROR(nRet);

	nRet = ZTRUE;
Exit0:
	return nRet;
}


ZBOOL ZafDriverDispatch(LPZDRIVER pZdriver)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nCVRet = ZFALSE;
	int arrnCVPosXY[2] = { 0, 0 };
	int nTestingCount = 0;
	LPZDRIVER pTmpZdriver = pZdriver->ptNext;



	nRet = ZTRUE;
Exit0:
	return nRet;
}