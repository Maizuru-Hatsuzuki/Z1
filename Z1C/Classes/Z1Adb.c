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

	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell screencap -p /sdcard/z1Caches/tmp.png");
	system(arrszCmd);
	Z1PRINTF_INFO(arrszCmd);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

ZBOOL Z1Adb_GetPathExists(const char* cszpTargetPath)
{
	ZBOOL nResult = ZFALSE;
	char arrszCmd[MAX_ADBCMD] = { 0 };
	char arrszResult[MAX_CMDRET] = { 0 };

	/*
	sprintf_s(arrszCmd, MAX_ADBCMD, "adb shell ls %s", cszpTargetPath);
	ZSystem(arrszCmd, arrszResult);
	Z1PRINTF_INFO(arrszCmd);
	Z1PRINTF_INFO(arrszResult);
	*/

	nResult = ZTRUE;
Exit0:
	return nResult;
}