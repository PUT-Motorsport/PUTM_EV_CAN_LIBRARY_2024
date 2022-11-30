
import numpy as np
import sys
c = __import__("csv")
b = __import__("bashsimulator")
csv = c.findAllCsv()
allDocs = []
if len(csv) ==  0:
    print("Terminated: No csv files found")
    sys.exit()
for entry in csv:
    print("Generating .h file for ", entry)
    allDocs.append(c.parseCsv(entry))
b.writeSim(allDocs)




