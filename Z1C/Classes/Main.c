#include "Z1C.h"
#include "Z1Adb.h"
#include "Z1Log.h"
#include "ZDriver.h"




int main()
{
	int nResult = ZFALSE;
	LPZDRIVER pZDriver = NULL;

	nResult = ZdCreateZDriver(&pZDriver, "G:\\CStudy\\Z1C\\Resource\\DriverEvent\\BGO.csv");
	Z1_PROCESS_ERROR(nResult);
	
	nResult = ZdInitAdb();
	Z1_PROCESS_ERROR(nResult);

	nResult = ZdDriverDispatch(pZDriver);
	Z1_PROCESS_ERROR(nResult);

	nResult = ZTRUE;
Exit0:
	return nResult;
}