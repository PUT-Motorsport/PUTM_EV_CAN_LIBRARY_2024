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
        temp = src.substr(0, position)
        if temp.empty():
            src.erase(0, 1)
            position = src.find(separator)
            continue
        else:
            result.append(temp)
        src.erase(0, position + 1)
        position = src.find(separator)
    result.append(src)

    return result, src
def parseCsv(fileName):
    fileName = "files/" +fileName
    file = open(fileName)
    splitLine = []
    line = []
    print("Perform additional name check? [Y/n]")
    check = 0
    if input() != 'n':
        check = 1
    oDoc = od.OutputDocument(fileName,check)

    while True:
        line = file.readline()
        if not line:
            break
