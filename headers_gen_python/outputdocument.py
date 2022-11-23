import os
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
    __deviceName = ""
    __deviceStateComments = []
    __deviceStates = []
    __verbatim = []
    __customEnumVec = []
    __canFrames = []
    __file = open("aaa", 'w')
    __file.close()
    os.system("rm aaa")
    def __init__(self ,genFileName ,performCheck):
        self.__performIllegalCharsCheck = performCheck
        self.__fileName = genFileName
        self.__fileName = self.__fileName.replace('.csv' ,'.hpp')
        self.__deviceName = ""
        self.__deviceStateComments = []
        self.__deviceStates = []
        self.__verbatim = []
        self.__customEnumVec = []
        self.__canFrames = []


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
        newFrame.frameName = None
        newFrame.dataType = []
        newFrame.dataNames = []
        newFrame.comments = []
        newFrame.frequency = None
        newFrame.id = None
        newFrame.frameName = self.__deviceName + '_' + newFrameName
        self.__canFrames.append(newFrame)
    def setFrequency(self,freq):
        self.__canFrames[len(self.__canFrames) - 1].frequency = freq

    def addID(self,newId):
        self.__canFrames[len(self.__canFrames) - 1].id = newId

    def addElementToCanFrame(self,dataType,dataName,comment):

        self.__canFrames[len(self.__canFrames) - 1].dataType.append(dataType)
        self.__canFrames[len(self.__canFrames) - 1].dataNames.append(dataName)
        self.__canFrames[len(self.__canFrames) - 1].comments.append(comment)

    def makeUppercase(self,target):
        return target.upper()
    def writeHeaderGuards(self):
        startTime = datetime.datetime.now()

        uppercaseName = self.makeUppercase(self.__deviceName)

        self.__file.write("//Generated on ")
        self.__file.write(str(startTime))
        self.__file.write("\n")
        self.__file.write("#ifndef ")
        self.__file.write(uppercaseName)
        self.__file.write("\n")
        self.__file.write("#define ")
        self.__file.write(uppercaseName)
        self.__file.write("\n")
        self.__file.write("\n")

        self.__file.write("#include <cstdint>")
        self.__file.write("\n")
        self.__file.write("\n")

    def writeVerbatim(self):

        if (len(self.__verbatim) == 0):
            return
        for  line in self.__verbatim:
            self.__file.write(line)
            self.__file.write("\n")
            self.__file.write("\n")

    def writeEnums(self):
        if (len(self.__customEnumVec) == 0):
            return

        self.__file.write("\n")

        for item in self.__customEnumVec:
            self.__file.write("enum struct " + item.name + ": uint8_t {")
            self.__file.write("\n\t")
            for iter in range(len(item.states)):
                self.__file.write("\n\t")
                self.__file.write(item.states[iter])
                self.__file.write(',')
                if item.comments[iter] != "\n":
                    self.__file.write("\t//")
                    self.__file.write(item.comments[iter])
                self.__file.write("\n\t")
            self.__file.write("};")
            self.__file.write("\n")
            self.__file.write("\n")

        self.__file.write("\n")

    def writeDeviceStates(self):

        self.__file.write("enum struct ")
        self.__file.write(self.__deviceName)
        self.__file.write("_states: uint8_t {")
        self.__file.write("\n")

        for iter in range(len(self.__deviceStates)):
            self.__file.write("\t")
            self.__file.write(self.removeIllegalChars(self.__deviceStates[iter]))
            self.__file.write(",")

            if (self.__deviceStateComments[iter] != "\n"):
                self.__file.write("\t//")
                self.__file.write(self.__deviceStateComments[iter])
            self.__file.write("\n")
        self.__file.write("};")
        self.__file.write("\n")

    def writeCanFrames(self,frame):
        assert (len(frame.dataNames) == len(frame.dataType))

        self.__file.write("struct __attribute__ ((packed)) ")
        self.__file.write(frame.frameName)
        self.__file.write("{")

        for iter in range(len(frame.dataNames)):

            if (frame.dataType[iter] == "state") :
                self.__file.write("\n\t")
                self.__file.write(self.__deviceName)
                self.__file.write("_states")
            else :
                self.__file.write("\n\t")
                self.__file.write(frame.dataType[iter])
            self.__file.write(" ")
            self.__file.write(self.removeIllegalChars(frame.dataNames[iter]))
            self.__file.write(";")

            if (frame.comments[iter] != "\n") :
                self.__file.write("//")
                self.__file.write(frame.comments[iter])
        self.__file.write("\n")
        self.__file.write("};")
        self.__file.write("\n")
        self.__file.write("\n")

    def writeIDs(self):
        self.__file.write("\n")
        for frame in self.__canFrames :
            frameName = frame.frameName
            upperCaseName = self.makeUppercase(frameName);
            self.__file.write("const uint16_t ")
            self.__file.write(upperCaseName)
            self.__file.write("_CAN_ID = 0x")
            self.__file.write(hex(frame.id))
            self.__file.write(";")
            self.__file.write("\n")

            self.__file.write("const uint8_t ")
            self.__file.write(upperCaseName)
            self.__file.write("_CAN_DLC = sizeof(")
            self.__file.write(frameName)
            self.__file.write(");")
            self.__file.write("\n")

            self.__file.write("const uint8_t ")
            self.__file.write(upperCaseName)
            self.__file.write("_FREQUENCY = ")
            self.__file.write(str(frame.frequency))
            self.__file.write(";")
            self.__file.write("\n")

        self.__file.write("\n")

    def writeHalDefinitons(self):

        for frame in self.__canFrames :

            upperCaseName = self.makeUppercase(frame.frameName);
            self.__file.write("const CAN_TxHeaderTypeDef can_tx_header_")
            self.__file.write(upperCaseName)
            self.__file.write("{")
            self.__file.write("\n")

            self.__file.write(upperCaseName)
            self.__file.write("_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, ")
            self.__file.write(upperCaseName)
            self.__file.write("_CAN_DLC, DISABLE};")
            self.__file.write("\n")
            self.__file.write("\n")

    def write(self):
        # if (not (file.is_open()))
        #     return false;
        self.__file = open(self.__fileName, 'w')
        self.writeHeaderGuards()

        self.writeVerbatim()

        self.writeEnums()

        self.writeDeviceStates()
        self.__file.write("\n")
        for frame in self.__canFrames :
            self.writeCanFrames(frame)

        self.writeIDs()

        self.writeHalDefinitons()

        self.__file.write("#endif")
        self.__file.write("\n")
        self.__file.write("\n")
        self.__file.close()

        return True