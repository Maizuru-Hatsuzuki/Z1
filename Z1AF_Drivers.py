from Z1EventDriver import Z1EventDriver


class Z1AF_Drivers():
    def __init__(self) -> None:
        self.arrszEventFile = ['FGO.json']
    
    def dispatch(self) -> None:
        for szEventFile in self.arrszEventFile:
            tmpDriver = Z1EventDriver("x", szEventFile)
            tmpDriver.dispatch()

### 登录
### 过场景
### 战斗
### 

if __name__ == "__main__":
    obj = Z1AF_Drivers()
    obj.dispatch()