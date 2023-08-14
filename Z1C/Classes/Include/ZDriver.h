#ifndef __ZDRIVER_H__
#define __ZDRIVER_H__


struct _tDriverEventDesc
{
	const int cnAdbTakeScreencap;
	const char* cszpEventFile;
	const char* cszpDesc;
};

struct _tDriverEventNode
{
	char arrszEventDesc[128];
	char arrszCVImgPath[MAX_PATH];
	int nMaxTesting;
};

struct _tZDriver
{
	struct _tDriverEventNode* ptEvent;
	struct _tZDriver* ptNext;
};

typedef struct _tDriverEventDesc DRIVEREVENT_DESC, * LPDRIVEREVENT_DESC;
typedef struct _tDriverEventNode DRIVEREVENT_NODE, * LPDRIVEREVENT_NODE;
typedef struct _tZDriver ZDRIVER, * LPZDRIVER;


ZBOOL ZdCreateZDriver(LPZDRIVER* ppZDriver, const char* cszpDriverFile);
ZBOOL ZdGetDriverEventsCsvFile(const char* cszpCsvFile, LPZDRIVER pZDriver);
ZBOOL ZdGetDriverEventsCsvFileNumFields(char* szpText, const int cnNum, char* szpRet);
ZBOOL ZdInitAdb();
ZBOOL ZdDriverDispatch(LPZDRIVER pZdriver);

#endif // !__ZDRIVER_H__
