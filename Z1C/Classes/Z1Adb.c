#include "Z1C.h"
#include "Z1Adb.h"
#include "Z1Log.h"
#include "Z1WinMgr.h"


ZBOOL Z1Adb_StartApp(const char* cszpAppPackage, const char* cszpAppActivity)
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell am start -n %s/%s", cszpAppPackage, cszpAppActivity);
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

ZBOOL Z1Adb_Mkdir(const char* cszpPhonePath)
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell mkdir %s", cszpPhonePath);
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

ZBOOL Z1Adb_PullFile(const char* cszpTargetFile, const char* cszpOutput)
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb pull %s %s", cszpTargetFile, cszpOutput);
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

ZBOOL Z1Adb_GetScreencap()
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell screencap -p %s", ROOTPATH_PHONESCREENCAP);
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

ZBOOL Z1Adb_TouchXY(const int cnX, const int cnY)
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell input tap %d %d", cnX, cnY);
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}