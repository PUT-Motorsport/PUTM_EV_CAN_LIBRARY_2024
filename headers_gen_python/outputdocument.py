
class CanFrame:
    frameName = None
    dataType = []
    dataNames = []
    comments = []
    frequency = None
    id = None

class CustomEnum:
    name = None
    states = []
    comments = []
class OutputDocument:
    __performIllegalCharsCheck = None
    __fileName = None
    __deviceName = None
    __deviceStateComments = []
    __deviceStates = []
    __verbatim = []
    def __init__(self ,genFileName ,performCheck):
        self.__performIllegalCharsCheck = performCheck
        self.__fileName = genFileName
        self.__fileName = self.__fileName.replace('.csv' ,'.hpp')
        __file = open(self.__fileName, 'w')

    def removeIllegalChars(self ,target):
        strCopy =target
        if self.__performIllegalCharsCheck:
            for ch in range(len(strCopy)):
                if strCopy[ch] == ' ' or strCopy[ch] == '-':
                    strCopy = strCopy[0:ch] + '_' + strCopy[ch + 1::]
        return strCopy

    def setDeviceName(self, devName):
        self.__deviceName = self.removeIllegalChars(devName)

    def addDeviceState(self, newDeviceState):
        self.__deviceStates.append(newDeviceState)

    def addDeviceStateComment(self,devStateComment):
        self.__deviceStateComments.append(devStateComment)

    def addVerbatim(self, text):
        self.__verbatim.append(text)