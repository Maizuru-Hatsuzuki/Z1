#ifndef __Z1ADB_H__
#define __Z1ADB_H__


#define Z1ADB_SCREENPOS_FRIESTHELPWAR_X 130
#define Z1ADB_SCREENPOS_FRIESTHELPWAR_Y 130

#define PHONEPACKAGE_BGO	"com.bilibili.fatego"
#define PHONEACTIVITY_BGO	"com.unity3d.player.UnityPlayerNativeActivity"


ZBOOL Z1Adb_StartApp(const char* cszpAppPackage, const char* cszpAppActivity);
ZBOOL Z1Adb_Mkdir(const char* cszpPhonePath);
ZBOOL Z1Adb_PullFile(const char* cszpTargetFile, const char* cszpOutput);
ZBOOL Z1Adb_GetScreencap();
ZBOOL Z1Adb_TouchXY(const int cnX, const int cnY);

#endif