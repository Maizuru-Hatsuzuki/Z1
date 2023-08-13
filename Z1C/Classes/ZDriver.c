#include "Z1C.h"
#include "ZDriver.h"
#include "Z1WinMgr.h"
#include "Z1Log.h"


void ZdCreateZDriver(LPZDRIVER* ppZDriver, const char* cszpDriverFile)
{
	LPZDRIVER pZDriver = (LPZDRIVER)malloc(sizeof(ZDRIVER));
	
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
			pNewZDriver->ptNext = pZDriver->ptNext;
			pZDriver->ptNext = pNewZDriver;
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

ZBOOL ZdGetDriverEventsCsvFileNumFields(const char* cszpText, const int cnNum, char* szpRet)
{
	ZBOOL nRet = ZFALSE;
	char* szpTok = NULL;
	char* szpTmp = strtok_s(cszpText, ",", &szpTok);
	
	for (size_t i = 1; i < cnNum; i++)
	{
		szpTmp = strtok_s(NULL, ",", &szpTok);
	}
	ZwmTrim(szpTmp, szpTmp);
	strcpy_s(szpRet, strlen(szpTmp) + 1, szpTmp);

	nRet = ZTRUE;

Exit0:
	if (NULL != cszpText)
	{
		free(cszpText);
	}
	return nRet;
}