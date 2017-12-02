#!/bin/bash
cd /home/pc/cpp/sudoku
PID=$(pidof gnome-sudoku)
if [ "x$PID" == "x" ]
then
    notify-send -i gnome-sudoku "Sudoku solver" "no sudoku found..."
    echo "no sudoku found..."
    exit 100
fi

WID=$(xdotool search --pid $PID | tail -n 1)
xdotool windowactivate $WID
TMP_IMG=$(mktemp sudoku-XXXXXX.png)
TMP_PNM=$(basename $TMP_IMG .png).pnm
gnome-screenshot -w -B -f $TMP_IMG
#cp $TMP_IMG screen.png
echo screenshot done...
#convert -fuzz 10% -fill white -opaque '#95918c' $TMP_IMG $TMP_PNM
#convert -fill black -opaque '#f2f1f0' $TMP_PNM $TMP_IMG
SIZE=$(python2.7 crop.py $TMP_IMG)
convert -crop $SIZE $TMP_IMG "$TMP_IMG.png"
mv $TMP_IMG.png $TMP_IMG
# find blue square
BLUE=$(python2.7 find_blue.py $TMP_IMG)
#convert $TMP_IMG $TMP_PNM
convert -fuzz 10% -fill white -floodfill +0+0 black "$TMP_IMG" "$TMP_PNM"
echo "cropped..."
#XML=$(gocr -m 258 -u 1 -p "db/"  -C "1-9" -f XML -i $TMP_PNM | grep box)
XML=$(gocr  -u 1 -p "db/"  -C "1-9" -f XML -i $TMP_PNM | grep box)

PARSED=$(echo $XML | grep -o "\( x\| y\| value\)=\"[^\"]*\"" | sed "s/[^0-9 ]//g")

RESULT=$(echo $(echo $SIZE | sed 's/[x+]/ /g') $PARSED | ./solver )

#echo $RESULT

notify-send -i gnome-sudoku "Sudoku solver" "solving sudoku for you"

xdotool windowactivate $WID
echo got result...
echo centering ...
$BLUE
echo filling result...
$RESULT
echo all done, exiting...
#rm $TMP_IMG $TMP_PNM
