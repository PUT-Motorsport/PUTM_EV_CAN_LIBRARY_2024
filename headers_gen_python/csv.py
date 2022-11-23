import glob, os
import re

od = __import__("outputdocument")


def findAllCsv():
    os.chdir("files")
    csvs = []
    for file in glob.glob("*.csv"):
        csvs.append(file)
    os.chdir("..")
    return csvs


def splitCsvLine(src):
    result = []
    separator = ','
    position = src.find(separator)
    while position != -1:
        temp = src[0:int(position)]
        if len(temp) == 0:
            src = src[1::]
            position = src.find(separator)
            continue
        else:

            result.append(temp)
        src = src[position + 1::]
        position = src.find(separator)
    if(len(src)!=0):
        result.append(src)
    if (len(result)) < 3:
        result.append("\n")
        result.append("\n")
    return result, src


def parseCsv(fileName):
    legendFlag = 1
    fileName = "files/" + fileName
    file = open(fileName)
    splitLine = []
    line = []
    print("Perform additional name check? [Y/n]")
    check = 0
    if input() != 'n':
        check = 1
    oDoc = od.OutputDocument(fileName, check)
    while True:
        line = file.readline()
        if not line:
            break

        splitLine, line = splitCsvLine(line)
        if len(splitLine) == 0:
            continue
        if splitLine[0] == "Device:":
            line = file.readline()
            splitLine, line = splitCsvLine(line)
            oDoc.setDeviceName(splitLine[0])
        elif splitLine[0] == "Device states:":
            line = file.readline()
            splitLine, line = splitCsvLine(line)
            while splitLine[0] != "" and splitLine[0] != "\n":
                oDoc.addDeviceState(splitLine[0])
                oDoc.addDeviceStateComment(splitLine[1])
                line = file.readline()
                splitLine, line = splitCsvLine(line)
        elif splitLine[0] == "Device states:":
            line = file.readline()
            splitLine, line = splitCsvLine(line)
            while splitLine[0] != "" and splitLine[0] != "\n":
                oDoc.addVerbatim(splitLine[0])
                line = file.readline()
                splitLine, line = splitCsvLine(line)
        elif splitLine[0] == "Enum" or splitLine[0] == "enum":
            oDoc.addNewEnum(splitLine[1])
            line = file.readline()
            splitLine, line = splitCsvLine(line)
            while splitLine[0] != "" and splitLine[0] != "\n":
                oDoc.addEnumElement(splitLine[0], splitLine[1])
                line = file.readline()
                splitLine, line = splitCsvLine(line)
        elif splitLine[0].find("frame") != -1:
            oDoc.newCanFrame(splitLine[1])
            if splitLine[0].find("Asynchronous") != -1:
                oDoc.setFrequency(0)
            else:
                freq = splitLine[2]
                rgx = "\\d+"
                match = re.search(rgx, freq)
                if match:
                    oDoc.setFrequency(int(match[0]))
            str = splitLine[3]
            if (str.find("0x") != -1):
                str = str[str.find("0x") + 2::]
                id = None
                try:
                    id = int(str, 16)
                except:
                    print("invalid argument")
                finally:
                    id = 0

                oDoc.addID(id)
            else:
                oDoc.addID(0)
            line = file.readline()

            line = file.readline()

            splitLine, line = splitCsvLine(line)
            while splitLine[0] != "" and splitLine[0] != "\n":
                oDoc.addElementToCanFrame(splitLine[0], splitLine[1], splitLine[2])
                line = file.readline()
                splitLine, line = splitCsvLine(line)


    oDoc.write()

    return True
