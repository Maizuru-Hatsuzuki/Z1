#include "Z1C.h"
#include "ZDriver.h"
#include "Z1WinMgr.h"
#include "Z1Log.h"
#include "Z1Adb.h"
#include "Z1CV.h"


ZBOOL ZdCreateZDriver(LPZDRIVER* ppZDriver, const char* cszpDriverFile)
{
	ZBOOL nRet = ZFALSE;
	LPZDRIVER pZDriver = (LPZDRIVER)malloc(sizeof(ZDRIVER));
	if (NULL == pZDriver)
	{
		__debugbreak();
	}
	pZDriver->ptEvent = NULL;
	pZDriver->ptNext = NULL;

	nRet = ZdGetDriverEventsCsvFile(cszpDriverFile, pZDriver);
	Z1_PROCESS_ERROR(nRet)

	*ppZDriver = pZDriver;

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdGetDriverEventsCsvFile(const char* cszpCsvFile, LPZDRIVER pZDriver)
{
	ZBOOL nRet = ZFALSE;
	int nCount = 0;
	char arrszRow[MAX_ZPRINTF] = { 0 };
	char szpTmp[MAX_ZPRINTF] = { 0 };
	char* szpPtr = NULL;
	FILE* pFile = NULL;
	LPZDRIVER pNewZDriver = NULL;
	LPZDRIVER ptmpZDriver = pZDriver;
	LPDRIVEREVENT_NODE ptNode = NULL;

	fopen_s(&pFile, cszpCsvFile, "r");
	Z1_PROCESS_ERROR(pFile);

	while (fgets(arrszRow, MAX_ZPRINTF, pFile))
	{
		if (0 != nCount)
		{
			pNewZDriver = (LPZDRIVER)malloc(sizeof(ZDRIVER));
			Z1_PROCESS_ERROR(pNewZDriver);
			ptNode = (LPDRIVEREVENT_NODE)malloc(sizeof(DRIVEREVENT_NODE));
			Z1_PROCESS_ERROR(ptNode);

			ZdGetDriverEventsCsvFileNumFields(_strdup(arrszRow), 1, szpTmp);
			strcpy_s(ptNode->arrszEventDesc, strlen(szpTmp) + 1, szpTmp);

			ZdGetDriverEventsCsvFileNumFields(_strdup(arrszRow), 2, szpTmp);
			strcpy_s(ptNode->arrszCVImgPath, strlen(szpTmp) + 1, szpTmp);

			ZdGetDriverEventsCsvFileNumFields(_strdup(arrszRow), 3, szpTmp);
			if (NULL == szpTmp)
			{
				ptNode->nMaxTesting = 0;
			}
			else
			{
				ptNode->nMaxTesting = atoi(szpTmp);
			}
			pNewZDriver->ptEvent = ptNode;
			pNewZDriver->ptNext = NULL;
			ptmpZDriver->ptNext = pNewZDriver;
			ptmpZDriver = pNewZDriver;
		}
		else
		{
		}

		nCount++;
	}
	Z1PRINTF_INFO("Load %s success, event count: %d.", cszpCsvFile, nCount - 1);

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdGetDriverEventsCsvFileNumFields(char* szpText, const int cnNum, char* szpRet)
{
	ZBOOL nRet = ZFALSE;
	char* szpTok = NULL;
	char* szpTmp = strtok_s(szpText, ",", &szpTok);
	
	for (size_t i = 1; i < cnNum; i++)
	{
		szpTmp = strtok_s(NULL, ",", &szpTok);
	}
	ZwmTrim(szpTmp, szpTmp);
	strcpy_s(szpRet, strlen(szpTmp) + 1, szpTmp);

	nRet = ZTRUE;

Exit0:
	if (NULL != szpText)
	{
		free((void*)szpText);
	}
	return nRet;
}

ZBOOL ZdGetPhoneProcessConfig(const char* cszpProcessConfigPath, LPDRIVERCONFIG* ppDriverConfig)
{
	ZBOOL nRet = ZFALSE;
	char szarrSection[10240] = { 0 };
	char szarrtmpKv[MAX_PATH] = { 0 };
	char* szpTok = NULL;
	DWORD dwFnRet = 0;
	DWORD dwSplitCount = 0;
	LPZARRAY pEvent = NULL;
	LPDRIVERCONFIG pDriverConfig = (LPDRIVERCONFIG)malloc(sizeof(DRIVERCONFIG));

	ZCreateArray(&pEvent, ZSTRING);
	ASSERT(pDriverConfig && pEvent);

	pDriverConfig->pEventFile = pEvent;
	pEvent->emType = ZSTRING;

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szDesc", NULL, pDriverConfig->szarrDesc, 128, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrDesc == NULL);

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szDriverEventDirPath", NULL, pDriverConfig->szarrDriverEventDirPath, MAX_PATH, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrDriverEventDirPath == NULL);

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szarrackage", NULL, pDriverConfig->szarrPackage, MAX_PATH, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrPackage == NULL);

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szActivity", NULL, pDriverConfig->szarrActivity, MAX_PATH, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrActivity == NULL);

	dwFnRet = GetPrivateProfileSectionA("Event", szarrSection, 1024, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(szarrSection == NULL);
	
	pEvent->append((void*)pEvent, (void*)szarrSection);
	dwSplitCount = strlen(szarrSection) + 1;
	
	while (dwFnRet > dwSplitCount)
	{
		strcpy_s(szarrtmpKv, szarrSection + strlen(szarrSection) + 1);
		pEvent->append((void*)pEvent, (void*)szarrtmpKv);
		dwSplitCount += strlen(szarrtmpKv) + 1;
	}

	pDriverConfig->pEventFile = pEvent;
	*ppDriverConfig = pDriverConfig;
	nRet = ZTRUE;

Exit0:
	return nRet;
}

ZBOOL ZdInitAdb(LPDRIVERCONFIG pDriverConfig)
{
	ZBOOL nRet = ZFALSE;
	Z1Adb_StartApp(pDriverConfig->szarrPackage, pDriverConfig->szarrActivity);
	Z1Adb_Mkdir("/sdcard/z1Caches");

	ZDeleteArray(pDriverConfig->pEventFile);
	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdDriverDispatch(LPZDRIVER pZdriver)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nCVRet = ZFALSE;
	int arrnCVPosXY[2] = { 0, 0 };
	int nTestingCount = 0;
	LPZDRIVER pTmpZdriver = pZdriver->ptNext;

	while (NULL != pTmpZdriver->ptNext)
	{
		nRet = Z1Adb_GetScreencap();
		Z1_PROCESS_ERROR(nRet);

		nRet = Z1Adb_PullFile(ROOTPATH_PHONESCREENCAP, ROOTPATH_CVIMG_TARGET);
		Z1_PROCESS_ERROR(nRet);

		nRet = ZcGetCVTargetPosition(pTmpZdriver->ptEvent->arrszCVImgPath, 0.8f, arrnCVPosXY, &nCVRet);
		Z1_PROCESS_ERROR(nRet);

		if (ZFALSE != nCVRet)
		{
			nRet = Z1Adb_TouchXY(arrnCVPosXY[0], arrnCVPosXY[1]);
			Z1_PROCESS_ERROR(nRet);

			pTmpZdriver = pTmpZdriver->ptNext;
			nTestingCount = 0;
		}
		else {}

		if (0 != pTmpZdriver->ptEvent->nMaxTesting && nTestingCount > pTmpZdriver->ptEvent->nMaxTesting)
		{
			pTmpZdriver = pTmpZdriver->ptNext;
			nTestingCount = 0;
		}
		else {}

		nTestingCount++;
		Sleep(5 * 1000);
	}

	nRet = ZTRUE;
Exit0:
	return nRet;
}
