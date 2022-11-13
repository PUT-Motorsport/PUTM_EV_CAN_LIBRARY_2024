
import numpy as np
import sys
c = __import__("csv")

csv = c.findAllCsv()

if len(csv) ==  0:
    print("Terminated: No csv files found")
    sys.exit()
for entry in csv:
    print("Generating .h file for ", entry)
    c.parseCsv(entry)





