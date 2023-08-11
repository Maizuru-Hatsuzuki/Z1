# -*-coding: utf-8 -*-


import time
import pathlib
from Z1Adb import Z1AdbHandler, PHONEINFO_REDMIK40, FGO_PACKAGE, FGO_ACTIVITY
from Z1CV import GetCVTargetPositionTL


if __name__ == "__main__":
    adbHandler = Z1AdbHandler(PHONEINFO_REDMIK40)
    adbHandler.startApp(FGO_PACKAGE, FGO_ACTIVITY)
    adbHandler.mkdir("/sdcard/z1Caches")
    arrszCase = ['loadingComplete.png', 'IndexloadingComplete.png', 'CloseNotify.png', 'fuyuki.png']
    n = 0

    while 1:
        adbHandler.getScreencap(str(pathlib.Path("Caches").absolute()))
        nX, nY = GetCVTargetPositionTL(str(pathlib.Path("data", "cvResource", arrszCase[n])))
        if 0 != nX:
            adbHandler.touchXYTransverseNox(nX, nY)
            n += 1

        if n >= len(arrszCase): break
        time.sleep(6)
    # time.sleep(30)