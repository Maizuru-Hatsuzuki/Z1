#include "Z1C.h"
#include "Z1Log.h"


void Z1Printf(const short csFlags, const char* cszpText, ...)
{
	char szarrTmp[MAX_ZPRINTF] = { 0 };
	char szarrPrintBuf[MAX_ZPRINTF] = { 0 };
	va_list pVa = NULL;

	va_start(pVa, cszpText);
	_vsnprintf_s(szarrTmp, MAX_ZPRINTF, MAX_ZPRINTF, cszpText, pVa);
	va_end(pVa);

	switch (csFlags)
	{
	case LOGLEVEL_INFO:
		sprintf_s(szarrPrintBuf, MAX_ZPRINTF, "[ZPRINTF INFO] %s\n", szarrTmp);
		break;

	case LOGLEVEL_WARING:
		sprintf_s(szarrPrintBuf, MAX_ZPRINTF, "[ZPRINTF WARING] %s\n", szarrTmp);
		break;

	case LOGLEVEL_ERROR:
		sprintf_s(szarrPrintBuf, MAX_ZPRINTF, "[ZPRINTF ERROR] %s\n", szarrTmp);
		break;

	case LOGLEVEL_DEBUG:
		sprintf_s(szarrPrintBuf, MAX_ZPRINTF, "[ZPRINTF DEBUG] %s\n", szarrTmp);
#ifndef _DEBUG
		goto Exit0;
#endif // !_DEBUG

		break;

	default:
		break;
	}

	printf(szarrPrintBuf);

Exit0:
	return;
}
