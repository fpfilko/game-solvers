#!/bin/bash

IMG_FILE=screen.png
CROP_IMG_FILE=screen-crop.png

function activate_mines {
PID=$(pidof gnome-mines)
if [ "x$PID" == "x" ]
then
    notify-send -i gnome-mines "Mines solver" "no mines found..."
    echo "no mines found..."
    exit 100
fi
WID=$(xdotool search --pid $PID | tail -n 1)
xdotool windowactivate $WID
}


cd /home/pc/cpp/mines
while true; do
    activate_mines
    sleep 0.1
    #gnome-screenshot -B -f $IMG_FILE
    import -window root $IMG_FILE
    echo "finding mines..."
    coords=$(./crop $IMG_FILE) #- return coordinates and size
    if [ "x$coords" = "x" ] ; then
        echo "no mines recognized"
        exit 1
    else
    convert -crop $coords $IMG_FILE $CROP_IMG_FILE
    echo "geting map..."
    size=$(./get_size $CROP_IMG_FILE)
    numbers=$(gocr  -u 1 -C "1-9" -f XML -i $CROP_IMG_FILE | grep box | grep -o "\( x\| y\| value\)=\"[^\"]*\"" | sed "s/[^0-9 ]//g")
#    echo "$(sed 's/[x+]/ /g' <<< $coords) $size $numbers"
    #echo $numbers $size $coords
    echo "solving...."
    comm=$(./solve <<< "$(sed 's/[x+]/ /g' <<< $coords) $size $numbers")
    ret=$?
    #echo $comm
    if [ -z "$comm" ]; then
        echo "nothing to do"
        exit 1;
    fi
    xdotool $comm
    if [ "$ret" != 0 ]; then
        echo "solver exited with nonzero status"
        break;
    fi
    sleep 0.5
fi
done
