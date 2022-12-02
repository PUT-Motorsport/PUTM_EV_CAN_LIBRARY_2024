
import re

def writeSim(documents):
    file = open("files/setup_hardwaresim.sh",'w')
    file.write("#!/bin/bash")
    file.write("\n")
    file.write("\n")


    file.write("modprobe vcan")
    file.write("\n")
    file.write("ip link add dev slcan0 type vcan")
    file.write("\n")
    file.write("ip link set up slcan0")
    file.write("\n")
    file.write("\n")

    file.write("while true")
    file.write("\n")
    file.write("do")
    file.write("\n")
    file.write("\n\t")
    f_num = 0
    for d in documents:
        file.write("#")
        file.write(d.returnDeviceName())
        file.write(":")
        file.write("\n\t")
        frames= d.returnFrames()
        for f in frames:
            if f.id !=0:
                file.write("#")
                file.write(f.frameName)
                file.write("\n\t")
                line = ""
                f_num = f_num+1
                if f.id < 10:
                    line ="frame" + str(f_num) + '="00' + str(hex(f.id)[2:]) + "#"
                elif f.id < 256:
                    line ='frame' + str(f_num) + '="0' + str(hex(f.id)[2:]) + "#"
                else:
                    line ='frame' + str(f_num) + '="' + str(hex(f.id)[2:]) + "#"
                for t in f.dataType:
                    line = line + "0"
                    if t.find("int") != -1:
                        for i in range((int(float(re.search(r'\d+', t).group())/8))-1):
                            line = line + "00"
                        line = line +'$(($RANDOM%10+1))'
                    else:
                        line = line+ '1'
                line = line + '"'
                file.write(line)
                file.write("\n\t")
                file.write("echo ${frame")
                file.write(str(f_num))
                file.write("}")
                file.write("\n\t")
                file.write("cansend slcan0 ${frame")
                file.write(str(f_num))
                file.write("}")
                file.write("\n\t")
                file.write("\n\t")
    file.write("\n")
    file.write("done")