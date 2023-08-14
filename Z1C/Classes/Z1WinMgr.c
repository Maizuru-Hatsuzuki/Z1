#include "Z1WinMgr.h"

ZBOOL ZSystem(const char* cszpCmd, char* szpResult)
{
	ZBOOL nResult = ZFALSE;
	char arrsztmp[MAX_ZPRINTF] = { 0 };
	FILE* pFile = NULL;

	pFile = _popen(cszpCmd, "r");
	Z1_PROCESS_ERROR(pFile);

	while (fgets(arrsztmp, sizeof(arrsztmp), pFile))
	{
		strcat_s(szpResult, sizeof(arrsztmp), arrsztmp);
	}
	_pclose(pFile);

	nResult = ZTRUE;
Exit0:
	return nResult;
}

void ZwmTrim(char* szpText, char* szpResult)
{
	char* szpTmp = szpText;
	int nStrLen = strlen(szpText);

	// delete right space.
	while (isspace(szpTmp[nStrLen - 1]))
	{
		szpTmp[--nStrLen] = 0;
	}

	// delete left space.
	while (*szpTmp && isspace(*szpTmp))
	{
		++szpTmp;
		--nStrLen;
	}

	memmove_s(szpResult, nStrLen + 1, szpTmp, nStrLen + 1);

Exit0:
	return;
}
