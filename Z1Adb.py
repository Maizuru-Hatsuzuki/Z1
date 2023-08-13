# -*-coding: utf-8 -*-
import os
import time
import json
import pathlib
from Macro import *




class Z1AdbHandler():
    def __init__(self, szPhoneModel) -> None:
        self.tConfig = {}
        self.szPhoneModel = szPhoneModel

        self.loadArgsPhoneInfo()

    def loadArgsPhoneInfo(self) -> None:
        with open("data\\{}.json".format(self.szPhoneModel), "r", encoding="utf-8") as f:
            self.tConfig = json.load(f)

        return

    def startApp(self, szPackage, szActivity) -> None:
        szPackageActiveity = "{}/{}".format(szPackage, szActivity)
        szCmd = "adb shell am start -n {}".format(szPackageActiveity)
        self.doAdbCmd(szCmd)

        return

    def shutdownApp(self, szPackage, szActivity) -> None:
        pass

    def mkdir(self, szPath) -> None:
        szCmd = "adb shell mkdir {}".format(szPath)
        self.doAdbCmd(szCmd)
        return
    
    def pushFile(self) -> None:
        pass

    def pullFile(self, szTargetFile, szOutputPath) -> None:
        szCmd = "adb pull {} {}".format(szTargetFile, szOutputPath)
        self.doAdbCmd(szCmd)
    
    def getScreencap(self, szOutputPath) -> str:
        szGetScreenCmd = "adb shell screencap -p /sdcard/z1Caches/tmp.png"
        self.doAdbCmd(szGetScreenCmd)

        self.pullFile("/sdcard/z1Caches/tmp.png", szOutputPath)
        return szOutputPath

    def touchXYTransverse(self, nX, nY, nCenterPoint = FALSE) -> None:
        # width: 0035
        # high: 0036
        nMaxWidth   = self.tConfig.get('PhoneInfo').get('n0035MaxWidth')
        nMaxHigh    = self.tConfig.get('PhoneInfo').get('n0036MaxHigh')
        fRateW      = self.tConfig.get('PhoneInfo').get('nResWidth') / nMaxWidth
        fRateH      = self.tConfig.get('PhoneInfo').get('nResHigh') / nMaxHigh

        if FALSE == nCenterPoint:
            fScreenX = nX * fRateH
            fScreenY = nY * fRateW
            szCmd = "adb shell input tap {} {}".format(nY, nX)
        else:
            fScreenX = self.tConfig.get('PhoneInfo').get('nResHigh') / 2
            fScreenY = self.tConfig.get('PhoneInfo').get('nResWidth') / 2
            szCmd = "adb shell input tap {} {}".format(fScreenX, fScreenY)
        
        self.doAdbCmd(szCmd)

        return
    
    def touchXYTransverseNox(self, nX, nY) -> None:
        szCmd = "adb shell input tap {} {}".format(nX, nY)
        self.doAdbCmd(szCmd)
        return

    def doAdbCmd(self, szCmd) -> None:
        print(szCmd)
        os.system(szCmd)

g_AdbHanlder = Z1AdbHandler(PHONEINFO_REDMIK40)

if __name__ == "__main__":
    adbHandler = Z1AdbHandler(PHONEINFO_REDMIK40)
    # adbHandler.startApp(FGO_PACKAGE, FGO_ACTIVITY)
    # adbHandler.mkdir("/sdcard/z1Caches")
    # arrszCase = ['loadingComplete.png', 'IndexloadingComplete.png', 'CloseNotify.png', 'fuyuki.png']
    # while 1:
    #     adbHandler.getScreencap(str(pathlib.Path("Caches").absolute()))
    adbHandler.getScreencap(str(pathlib.Path("Caches").absolute()))

    #     time.sleep(3)
    # time.sleep(30)
    # for i in range(2):
    #     adbHandler.touchXYTransverse(0x5, 0x5)
    #     time.sleep(15)
    # adbHandler.touchXYTransverse(8023, 17177)
    # time.sleep(15)
    # adbHandler.touchXYTransverse(1920, 9613)
    
    