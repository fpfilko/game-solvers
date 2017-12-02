from PIL import Image as I
import sys
import math


imin = I.open(sys.argv[1])
imin.convert('RGB')
pixin = imin.load()
s = imin.size
minx = s[0]
maxx = 0
miny = s[0]
maxy = 0
for x in range(s[0]):
    for y in range(s[1]):
        if pixin[x, y][0] == 0 and pixin[x, y][1] == 0 and pixin[x, y][2] == 0:
            if x < minx:
                minx=x
            if x > maxx:
                maxx=x
            if y > maxy:
                maxy=y
            if y < miny:
                miny=y
#        if pixin[x, y][1] > 80:
#            pixin[x, y] = (255,255,255)
#        else:
#            pixin[x, y] = (0,0,0)
#
#imin.save(sys.argv[1])
                
print "%dx%d+%d+%d" % ( maxx - minx + 1 , maxy - miny + 1, minx, miny)
#print "650x650+256+67"
