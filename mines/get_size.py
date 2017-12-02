#!/usr/bin/env python
from PIL import Image as I
import sys
import math

#TODO output constants to translate matrix + given matrix.

imin = I.open(sys.argv[1]).convert('RGB')
pixin = imin.load()
imout = imin.copy()
pixout = imout.load()
s = imin.size
minx = s[0]
maxx = 0
miny = s[0]
maxy = 0
sep = True
dimx = 0
cx=[]
cy=[]
for x in range(s[0]):
#        186 189 182 - normal
#        211 215 207 - hover
#        222 222 220 - uncover
        if pixin[x, 2] == (186,189,182) or pixin[x, 2] == (211,215,207) or pixin[x, 2] == (222,222,220):
            if sep:
              dimx = dimx + 1
              cx.append(x)
              sep = False
        else:
            sep = True

sep = True
dimy = 0
for y in range(s[1]):
#        186 189 182 - normal
#        211 215 207 - hover
#        222 222 220 - uncover
        if pixin[2, y] == (186,189,182) or pixin[2, y] == (211,215,207) or pixin[2, y] == (222,222,220):
            if sep:
              dimy = dimy + 1
              cy.append(y)
              sep = False
        else:
            sep = True


print "%d %d" % (dimy, dimx)

constx = int(s[0]*0.23/dimx)
consty = int(s[1]*0.23/dimy)

#print consty, constx

for j in range(dimy):
    ss = ""
    for i in range(dimx):
        sx=cx[i]+constx
        sy=cy[j]+consty
        pixout[sx,sy] = (0,0,0)
        if pixin[sx, sy] == (186,189,182):
            ss = ss + "0 "
        elif pixin[sx, sy] == (211,215,207):
            ss = ss + "0 "
        elif pixin[sx, sy] == (222,222,220):
            ss = ss + "9 "
        else:
        # mine
            ss = ss + "10 "
#            f = open("problems.txt", "a")
#            f.write("problem with field [" + str(i) + "," + str(j) + "] -> [" + str(sx) + "," + str(sy) + "]/"+str(s)+", color is (" + str(pixin[sx,sy]) + ")\n")
    print ss

imout.save("screen-modif.png")
