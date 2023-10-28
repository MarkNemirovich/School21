#!/bin/bash

file=$1
strOld=$2
strNew=$3

if  [ ! -f $file ]; then
	echo "No such file"
	exit
fi

if [ $strOld = $strNew ]; then
	echo "No need to change to the same string"
	exit
fi

if [ $strNew = '' ]; then
        echo "No need to change to empty string"
	exit
fi

$(grep -q "$strOld" $file)
if [ $? -eq 0 ]; then
    sed -i '' "s/$strOld/$strNew/g" $file
    echo "src/$file - $(stat -f%z $file) - $(date "+%Y-%m-%d %H:%M") - $(shasum -a 256 $file  | awk '{print $1}') - sha256" >> files.log
fi
