#-*- coding: utf-8 -*-

import json
import pathlib
import time
from Z1CV import GetCVTargetPositionTL
from Z1Adb import g_AdbHanlder
from Macro import *

g_nInitFlag = ZFALSE

class Z1EventDriver():
    def __init__(self, szDriverDesc, szDriverFile, nAdbTakeScreencap = 15) -> None:
        self.szDriverDesc = szDriverDesc
        self.nAdbTakeScreencap = nAdbTakeScreencap
        self.tConfig = {}
        self.arrtDrvierEvents = []

        self.initConfig(szDriverFile)
        if ZFALSE == g_nInitFlag:
            self.initApp()

    def __str__(self) -> str:
        szDesc = "Z1EventDriver - {}".format(self.szDriverDesc)
        return szDesc

    def initConfig(self, szDriverFile) -> None:
        with open(pathlib.Path('data', 'GameDrivers', szDriverFile), 'r', encoding='utf-8') as f:
            self.tConfig = json.load(f)

        self.arrtDrvierEvents = self.tConfig.get('DriverEvents')
        print("loading {} success, version: {}".format(szDriverFile, self.tConfig.get('Version')))
        return
    
    def initApp(self):
        g_AdbHanlder.startApp(FGO_PACKAGE, FGO_ACTIVITY)
        g_AdbHanlder.mkdir("/sdcard/z1Caches")

        global g_nInitFlag 
        g_nInitFlag = ZTRUE

    def dispatch(self) -> None:
        nEventSerial = 0
        nEventCount = len(self.arrtDrvierEvents)
        szRootCVImgPath = self.tConfig.get('CVImgRootPath')

        while 1:
            if nEventSerial > nEventSerial:
                break
            
            szCVImg = self.arrtDrvierEvents[nEventSerial].get('CVImg')
            g_AdbHanlder.getScreencap(str(pathlib.Path("Caches").absolute()))
            nX, nY = GetCVTargetPositionTL(str(pathlib.Path(szRootCVImgPath, szCVImg)))

            if 0 != nX:
                g_AdbHanlder.touchXYTransverseNox(nX, nY)
                print("{}/{} event success.".format(nEventSerial, nEventCount))
                nEventSerial += 1

            else:
                time.sleep(self.nAdbTakeScreencap)
                continue