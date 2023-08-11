# -*-coding: utf-8 -*-

import win32gui


class Z1_WindowControl():
    def __init__(self) -> None:
        self.szProcessName = "Nox.exe"
        self.szProcessClass = "Qt5QWindowIcon"
        self.szWindowCaption = "夜神模拟器"
        self.hProcess = win32gui.FindWindow(self.szProcessClass, self.szWindowCaption)
        assert(self.hProcess)

    def SetWindowPositionAndSize(self) -> None:
        win32gui.MoveWindow(self.hProcess, 0, 0, 994, 569, True)

    def SetWindowTarget(self) -> None:
        win32gui.SetForegroundWindow(self.hProcess)

    def dispatch(self) -> None:
        self.SetWindowPositionAndSize()
        self.SetWindowTarget()


if __name__ == "__main__":
    obj = Z1_WindowControl()
    obj.dispatch()