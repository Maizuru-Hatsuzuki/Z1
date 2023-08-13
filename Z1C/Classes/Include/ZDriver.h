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


void ZdCreateZDriver(LPZDRIVER* ppZDriver);
ZBOOL ZdGetDriverEventsCsvFile(const char* cszpCsvFile, LPZDRIVER pZDriver);
ZBOOL ZdGetDriverEventsCsvFileNumFields(const char* cszpText, const int cnNum);

#endif // !__ZDRIVER_H__
