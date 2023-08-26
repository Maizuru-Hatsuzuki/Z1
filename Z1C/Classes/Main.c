#include "Z1C.h"
#include "Z1Adb.h"
#include "Z1Log.h"
#include "ZDriver.h"



int main()
{
	int nResult = ZFALSE;
	LPZDRIVER pZDriver = NULL;
	LPDRIVERCONFIG pZDriverConfig = NULL;
	
	nResult = ZdGetPhoneProcessConfig(PHONEPROCESSCONFIG_BGO, &pZDriverConfig);
	Z1_PROCESS_ERROR(nResult);

	nResult = ZdCreateZDriver(&pZDriver, pZDriverConfig);
	Z1_PROCESS_ERROR(nResult);
	
	nResult = ZdInitAdb(pZDriverConfig);
	Z1_PROCESS_ERROR(nResult);

	nResult = ZdDriverDispatch(pZDriver);
	Z1_PROCESS_ERROR(nResult);

	nResult = ZTRUE;
Exit0:
	free(pZDriver);
	ZDeleteArray(pZDriverConfig->pEventFile);
	return nResult;
}