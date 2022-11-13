import glob, os
od = __import__("outputdocument")
def findAllCsv():
    os.chdir("files")
    csvs = []
    for file in glob.glob("*.csv"):
        csvs.append(file)
    os.chdir("..")
    return csvs

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

