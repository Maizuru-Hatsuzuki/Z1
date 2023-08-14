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

ZBOOL ZdInitAdb()
{
	ZBOOL nRet = ZFALSE;
	Z1Adb_StartApp(PHONEPACKAGE_BGO, PHONEACTIVITY_BGO);
	Z1Adb_Mkdir("/sdcard/z1Caches");

	nRet = ZTRUE;
Exit0:
	return nRet;
}

ZBOOL ZdDriverDispatch(LPZDRIVER pZdriver)
{
	ZBOOL nRet = ZFALSE;
	ZBOOL nCVRet = ZFALSE;
	int arrnCVPosXY[2] = { 0, 0 };
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
		}
		else
		{
		}
		Sleep(5 * 1000);
	}

	nRet = ZTRUE;
Exit0:
	return nRet;
}
