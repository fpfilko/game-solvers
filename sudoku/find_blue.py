from PIL import Image as I
import sys
import math


imin = I.open(sys.argv[1])
imin = imin.convert('RGB')
pixin = imin.load()
s = imin.size
sx=s[0]
sy=s[1]
bluex=0
bluey=0
bluen=0
for x in range(s[0]):
    for y in range(s[1]):
        if pixin[x, y][0] == 172 and pixin[x, y][1] == 196 and pixin[x, y][2] == 221:
            bluex += x
            bluey += y
            bluen += 1
        if pixin[x, y][0] == 179 and pixin[x, y][1] == 204 and pixin[x, y][2] == 230:
            bluex += x
            bluey += y
            bluen += 1
        if pixin[x, y][1] > 80:
            pixin[x, y] = (255,255,255)
        else:
            pixin[x, y] = (0,0,0)

imin.save(sys.argv[1])
command = ""

if bluen < 20:
    for i in range(10):
        command += "Left "
    for i in range(8):
        command += "Up "
else:
    bluex = bluex * 9 / bluen / sx
    bluey = bluey * 9 / bluen / sy
    for i in range(bluex):
        command += "Left "
    for i in range(bluey):
        command += "Up "
if command != "":
    print "xdotool key " + command

