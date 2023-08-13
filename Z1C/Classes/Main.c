#include "Z1C.h"
#include "Z1Adb.h"
#include "Z1Log.h"
#include "ZDriver.h"

int main()
{
	int nResult = ZTRUE;
	Z1PRINTF_INFO("Z1 c develop, version: 1.0\n");
	//nResult = Z1Adb_StartApp(PHONEPACKAGE_BGO, PHONEACTIVITY_BGO);
	ZdGetDriverEventsCsvFile("G:\\Z1C\\Resource\\DriverEvent\\BGO.csv", NULL);
	return 1;
}