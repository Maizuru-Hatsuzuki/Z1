#ifndef __ZDRIVER_H__
#define __ZDRIVER_H__

#include "Z1C.h"

#define PHONEPROCESSCONFIG_BGO "..\\Resource\\DriverConfig\\BGO.ini"


struct _tDriverConfig
{
	char szarrDesc[128];
	char szarrDriverEventDirPath[MAX_PATH];
	char szarrPackage[MAX_PATH];
	char szarrActivity[MAX_PATH];
	LPZARRAY pEventFile;
};

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

typedef struct _tDriverConfig DRIVERCONFIG, * LPDRIVERCONFIG;
typedef struct _tDriverEventDesc DRIVEREVENT_DESC, * LPDRIVEREVENT_DESC;
typedef struct _tDriverEventNode DRIVEREVENT_NODE, * LPDRIVEREVENT_NODE;
typedef struct _tZDriver ZDRIVER, * LPZDRIVER;


ZBOOL ZdCreateZDriver(LPZDRIVER* ppZDriver, const char* cszpDriverFile);
ZBOOL ZdGetDriverEventsCsvFile(const char* cszpCsvFile, LPZDRIVER pZDriver);
ZBOOL ZdGetDriverEventsCsvFileNumFields(char* szpText, const int cnNum, char* szpRet);
ZBOOL ZdGetPhoneProcessConfig(const char* cszpProcessConfigPath, LPDRIVERCONFIG* ppDriverConfig);
ZBOOL ZdInitAdb(LPDRIVERCONFIG pDriverConfig);
ZBOOL ZdDriverDispatch(LPZDRIVER pZdriver);

#endif // !__ZDRIVER_H__
