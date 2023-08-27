#include "Z1C.h"
#include "ZDriver.h"
#include "Z1WinMgr.h"
#include "Z1Log.h"
#include "Z1Adb.h"
#include "Z1CV.h"
#include "Z1AF.h"


ZBOOL ZdCreateZDriver(LPZDRIVER* ppZDriver, LPDRIVERCONFIG pDriverFileConfig)
{
	ZBOOL nRet							= ZFALSE;
	char szarrEventFilePath[MAX_PATH]	= { 0 };
	void* vpEventFilename				= NULL;
	LPZDRIVER pZDriver					= (LPZDRIVER)malloc(sizeof(ZDRIVER));

	if (NULL == pZDriver)
	{
		__debugbreak();
	}
	pZDriver->ptEvent = NULL;
	pZDriver->ptNext = NULL;

	for (size_t i = 0; i < pDriverFileConfig->pEventFile->unCount; i++)
	{
		pDriverFileConfig->pEventFile->findPos(pDriverFileConfig->pEventFile, i, &vpEventFilename);
		Z1_PROCESS_ERROR(vpEventFilename);

		sprintf_s(szarrEventFilePath, MAX_PATH, "%s\\%s", pDriverFileConfig->szarrDriverEventDirPath, (char*)vpEventFilename);
		nRet = ZdGetDriverEventsCsvFile(szarrEventFilePath, pZDriver);
		Z1_PROCESS_ERROR(nRet);
	}

	*ppZDriver = pZDriver;

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdGetDriverEventsCsvFile(const char* cszpCsvFile, LPZDRIVER pZDriver)
{
	ZBOOL nRet = ZFALSE;
	int nCount = 0;
	char szarrRow[MAX_ZPRINTF] = { 0 };
	char szpTmp[MAX_ZPRINTF] = { 0 };
	char* szpPtr = NULL;
	FILE* pFile = NULL;
	LPZDRIVER pNewZDriver = NULL;
	LPZDRIVER ptmpZDriver = pZDriver;
	LPDRIVEREVENT_NODE ptNode = NULL;

	fopen_s(&pFile, cszpCsvFile, "r");
	Z1_PROCESS_ERROR(pFile);

	while (fgets(szarrRow, MAX_ZPRINTF, pFile))
	{
		if (0 != nCount)
		{
			pNewZDriver = (LPZDRIVER)malloc(sizeof(ZDRIVER));
			Z1_PROCESS_ERROR(pNewZDriver);
			ptNode = (LPDRIVEREVENT_NODE)malloc(sizeof(DRIVEREVENT_NODE));
			Z1_PROCESS_ERROR(ptNode);

			ZdGetDriverEventsCsvFileNumFields(_strdup(szarrRow), 1, szpTmp);
			strcpy_s(ptNode->arrszEventDesc, strlen(szpTmp) + 1, szpTmp);

			ZdGetDriverEventsCsvFileNumFields(_strdup(szarrRow), 2, szpTmp);
			strcpy_s(ptNode->arrszCVImgPath, strlen(szpTmp) + 1, szpTmp);

			ZdGetDriverEventsCsvFileNumFields(_strdup(szarrRow), 3, szpTmp);
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
	const short csMaxEventFieldNum = 10;
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

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szPackage", NULL, pDriverConfig->szarrPackage, MAX_PATH, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrPackage == NULL);

	dwFnRet = GetPrivateProfileStringA("ZDriver", "szActivity", NULL, pDriverConfig->szarrActivity, MAX_PATH, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(pDriverConfig->szarrActivity == NULL);

	dwFnRet = GetPrivateProfileSectionA("Event", szarrSection, 1024, cszpProcessConfigPath);
	Z1_PROCESS_SUCCESS(szarrSection == NULL);
	
	strcpy_s(szarrtmpKv, szarrSection);
	dwSplitCount = strlen(szarrSection) + 1;
	szarrtmpKv[strlen(szarrtmpKv) - 1] = '\0';
	pEvent->append((void*)pEvent, (void*)(szarrtmpKv + csMaxEventFieldNum), dwSplitCount);
	
	while (dwFnRet > dwSplitCount)
	{
		strcpy_s(szarrtmpKv, szarrSection + dwSplitCount);
		dwSplitCount = dwSplitCount + strlen(szarrtmpKv) + 1;
		szarrtmpKv[strlen(szarrtmpKv) - 1] = '\0';

		pEvent->append((void*)pEvent, (void*)(szarrtmpKv + csMaxEventFieldNum), strlen(szarrtmpKv) + 1);
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
	system("adb devices");
	Z1Adb_StartApp(pDriverConfig->szarrPackage, pDriverConfig->szarrActivity);
	Z1Adb_Mkdir("/sdcard/z1Caches");

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdDoTouch(const char* cszpCVTargetImg, ZBOOL* pnRet)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nCVRet = ZFALSE;
	int narrPosRes[2] = { 0, 0 };

	nRet = Z1Adb_GetScreencap();
	Z1_PROCESS_ERROR(nRet);

	nRet = Z1Adb_PullFile(ROOTPATH_PHONESCREENCAP, ROOTPATH_CVIMG_TARGET);
	Z1_PROCESS_ERROR(nRet);

	nRet = ZcGetCVTargetPosition(cszpCVTargetImg, 0.8f, narrPosRes, &nCVRet);
	Z1_PROCESS_ERROR(nRet);

	if (ZFALSE != nCVRet)
	{
		nRet = Z1Adb_TouchXY(narrPosRes[0], narrPosRes[1]);
		Z1_PROCESS_ERROR(nRet);
		Z1PRINTF_INFO("Touch event: %s", cszpCVTargetImg);

		*pnRet = ZTRUE;
	}
	else { *pnRet = ZFALSE; }

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdDoBasicEvent(const char** cszppBasicEvent, const int cnMaxBasicEventLen)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nTouchRet = ZFALSE;
	int narrPosRes[2] = { 0, 0 };

	for (size_t i = 0; i < cnMaxBasicEventLen; i++)
	{
		nRet = ZdDoTouch(*(cszppBasicEvent + i), &nTouchRet);
		Z1_PROCESS_ERROR(nRet);
	}

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdDriverDispatch(LPZDRIVER pZdriver, enum ZSUPPORT_CLEINT emClient)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nTouchRet = ZFALSE;
	int arrnCVPosXY[2] = { 0, 0 };
	int nTestingCount = 0;
	LPZDRIVER pTmpZdriver = pZdriver->ptNext;

	while (NULL != pTmpZdriver->ptNext)
	{
		// do basic test case check.
		switch (emClient)
		{
		case ZSUPPORT_CLIENT_BGO:
			nRet = ZafGetBasicEvent();
			Z1_PROCESS_ERROR(nRet);
			break;

		default:
			break;
		}

		// do pTmpZdriver(.csv) test case check.
		//nRet = ZdDoTouch(pTmpZdriver->ptEvent->arrszCVImgPath, &nTouchRet);
		//Z1_PROCESS_ERROR(nRet);
		//if (ZFALSE != nTouchRet)
		//{
		//	pTmpZdriver = pTmpZdriver->ptNext;
		//	nTestingCount = 0;
		//}
		//else {}

		//if (0 != pTmpZdriver->ptEvent->nMaxTesting && nTestingCount > pTmpZdriver->ptEvent->nMaxTesting)
		//{
		//	pTmpZdriver = pTmpZdriver->ptNext;
		//	nTestingCount = 0;
		//}
		//else {}

		nTestingCount++;
		Sleep(5 * 1000);
	}

	nRet = ZTRUE;
Exit0:
	return nRet;
}
