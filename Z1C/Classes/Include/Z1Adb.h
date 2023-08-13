#ifndef __Z1ADB_H__
#define __Z1ADB_H__


#define Z1_ADBTOUCH(nX, nY)

#define PHONEPACKAGE_BGO	"com.bilibili.fatego"
#define PHONEACTIVITY_BGO	"com.unity3d.player.UnityPlayerNativeActivity"


ZBOOL Z1Adb_StartApp(const char* cszpAppPackage, const char* cszpAppActivity);
ZBOOL Z1Adb_Mkdir(const char* cszpPhonePath);
ZBOOL Z1Adb_PullFile(const char* cszpTargetFile, const char* cszpOutput);
ZBOOL Z1Adb_GetScreencap();
ZBOOL Z1Adb_GetPathExists(const char* cszpTargetPath);

#endif