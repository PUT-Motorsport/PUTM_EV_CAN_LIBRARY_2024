import glob, os

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
    result.append(src)

    return result, src


def parseCsv(fileName):
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
            while splitLine[0] != "" and splitLine[0] != "\r":
                oDoc.addDeviceState(splitLine[0])
                oDoc.addDeviceStateComment(splitLine[1])
                line = file.readline()
                splitLine, line = splitCsvLine(line)
        elif splitLine[0] == "Device states:":
            line = file.readline()
            splitLine, line = splitCsvLine(line)
            while splitLine[0] != "" and splitLine[0] != "\r":
                oDoc.addVerbatim(splitLine[0])
                line = file.readline()
                splitLine, line = splitCsvLine(line)

