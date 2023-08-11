import cv2
import numpy
from Z1Adb import Z1AdbHandler, PHONEINFO_REDMIK40
from matplotlib import pyplot as plt


def GetCVTargetPositionTL(szTargetPath: str, fThreshold=0.8) -> tuple:
    cvTemplate = cv2.imread("Caches\\tmp.png")
    cvTarget = cv2.imread(szTargetPath)
    mRes = cv2.matchTemplate(cvTarget, cvTemplate, cv2.TM_CCOEFF_NORMED)

    _, nMaxVal, _, arrnTopLeft = cv2.minMaxLoc(mRes)
    if nMaxVal <= fThreshold:
        arrnTopLeft = (0, 0)
    else:
        print("match, nMaxVal: ", nMaxVal)

    return arrnTopLeft    

def template_demo():
    cvTemplate = cv2.imread("Caches\\tmp.png")
    cvTarget = cv2.imread("data\\cvResource\\fuyuki.png")
    #cv2.imshow("target image", target)
    th, tw = cvTarget.shape[:2]
    result = cv2.matchTemplate(cvTarget, cvTemplate, cv2.TM_CCOEFF_NORMED)

    _, nMaxLoc, _, arrnTopLeft = cv2.minMaxLoc(result)
    tl = arrnTopLeft
    br = (tl[0] + tw, tl[1] + th)

    # draw border
    cv2.rectangle(cvTemplate, tl, br, (0, 0, 255), 2)
    print(tl, nMaxLoc)
    print(br)
    cv2.imshow("match-" + str(cv2.TM_CCOEFF_NORMED), cvTemplate)

    return arrnTopLeft

if __name__ == "__main__":
    template_demo()
