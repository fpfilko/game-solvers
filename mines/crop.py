from PIL import Image as I
import sys
import math

#TODO output constants to translate matrix + given matrix.

def search(pix, x, y, c):
    lmaxx=x
    lmaxy=y
    lminx=x
    lminy=y
    pix[x,y] = (0,0,0)
    pole=[(x,y)]
    cnt = 1;
    while len(pole) > 0:
        x,y = pole[-1]
        del pole[-1]
        if x > lmaxx:
            lmaxx=x
        if y > lmaxy:
            lmaxy=y
        if x < lminx:
            lminx=x
        if y < lminy:
            lminy=y
        if(x>0 and pix[x-1,y] == c):
            #print "lavo"
            pix[x-1,y]=(0,0,0)
            pole.append((x-1,y))
            cnt = cnt+1
        if(y>0 and pix[x,y-1] == c):
           # print "dole"
            pix[x,y-1]=(0,0,0)
            pole.append((x,y-1))
            cnt = cnt+1
        if(y<s[1]-1 and pix[x,y+1] == c):
            #print "hore" 
            pix[x,y+1]=(0,0,0)
            pole.append((x,y+1))
            cnt = cnt+1
        if(x<s[0]-1 and pix[x+1,y] == c):
            #print "pravo"
            pix[x+1,y]=(0,0,0)
            pole.append((x+1,y))
            cnt = cnt+1
    return (cnt, lmaxx, lminx,  lmaxy, lminy)
    

imin = I.open(sys.argv[1]).convert("RGB")
pixin = imin.load()
s = imin.size
minx = s[0]
maxx = 0
miny = s[1]
maxy = 0

for x in range(s[0]):
    for y in range(s[1]):
#        186 189 182 - normal
#        211 215 207 - hover
#        222 222 220 - uncover
        
        if pixin[x, y] == (186,189,182) or pixin[x, y] == (202,206,198) or pixin[x, y] == (222,222,220):
            cnt, lmaxx, lminx, lmaxy, lminy = search(pixin, x, y, pixin[x,y])
            if cnt > 100:
                if lminx < minx:
                    minx=lminx
                if lmaxx > maxx:
                    maxx=lmaxx
                if lmaxy > maxy:
                    maxy=lmaxy
                if lminy < miny:
                    miny=lminy
#        if pixin[x, y][1] > 80:
#            pixin[x, y] = (255,255,255)
#        else:
#            pixin[x, y] = (0,0,0)
#
#imin.save(sys.argv[1])
if maxx - minx < 30 or maxy-miny < 30:
    #print [maxx,minx,maxy,miny]
    sys.exit(1)
                
print "%dx%d+%d+%d" % ( maxx - minx + 1 , maxy - miny + 1, minx, miny)
#print "650x650+256+67"
