from enum import Enum
import datetime
class CanFrame:
    frameName = None
    dataType = []
    dataNames = []
    comments = []
    frequency = None
    id = None
class CustomEnum:
    name =None
    states = []
    comments = []
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
    __customEnumVec = []
    __canFrames = []
    __file = None
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

    def addNewEnum(self,name):
        newEnum = CustomEnum()
        newEnum.name = name
        self.__customEnumVec.append(newEnum)

    def addEnumElement(self,name, comment):
        if len(self.__customEnumVec) == 0:
            raise Exception("Custom Enum vector is empty")

        lastEnum = self.__customEnumVec.back()
        lastEnum.states.append(name)
        lastEnum.comments.append(comment)

    def newCanFrame(self,newFrameName):
        newFrame =CanFrame()
        newFrame.frameName = self.__deviceName + '_' + newFrameName

        self.__canFrames.append(newFrame)
    def setFrequency(self,freq):
        self.__canFrames[len(self.__canFrames) - 1].frequency = freq

    def addID(self,newId):
        self.__canFrames[len(self.__canFrames) - 1].id = newId

    def addElementToCanFrame(self,dataType,dataName,comment):
        self.__canFrames[len(self.__canFrames) - 1].dataTypes.append(dataType)
        self.__canFrames[len(self.__canFrames) - 1].dataNames.append(dataName)
        self.__canFrames[len(self.__canFrames) - 1].comments.append(comment)

    def makeUppercase(self,target):
        for  ch in target:
            ch = ch.upper()
        return target;
    def writeHeaderGuards(self):
        startTime = datetime.datetime.now()

        uppercaseName = self.makeUppercase(self.__deviceName)

        self.__file.write("//Generated on ")
        self.__file.write(startTime)
        self.__file.write("#ifndef ")
        self.__file.write(uppercaseName)
        self.__file.write("\n")
        self.__file.write("#define ")
        self.__file.write(uppercaseName)
        self.__file.write("\n")
        self.__file.write("\n")

        self.__file.write("#include <cstdint>")
        self.__file.write("\n")
        self.__file.write("#include \"hal_can.hpp\"")
        self.__file.write("\n")
        self.__file.write("#include \"message_abstraction.hpp\"")
        self.__file.write("\n")
        self.__file.write("\n")

    def write(self):
        # if (not (file.is_open()))
        #     return false;

        self.writeHeaderGuards();

        self.writeVerbatim();

        writeEnums();

        writeDeviceStates();
        file << std::endl;
        for (auto const & frame: canFrames)
            writeCanFrames(frame);

        writeIDs();

        writeHalDefinitons();

        file << "#endif" << std::endl << std::endl;

        return true;