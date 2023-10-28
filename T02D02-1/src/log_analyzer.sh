#!bin/bash

file=$1

if  [ ! -f $file ]; then
    echo "File is not found"
    exit
fi

echo "total amount of logs = $(wc -l < $file)"

fileNames=$(cut -d ' ' -f1 $file)
#echo $fileNames
fileHashes=$(cut -d ' ' -f8 $file)
#echo $fileHashes

uniqFileNames=$(echo $fileNames | xargs -n1 | sort | uniq | xargs)
uniqFileHashes=$(echo $fileHashes | xargs -n1 | sort | uniq | xargs)

countUniqFileNames="${uniqFileNames//[^ ]}"
echo "total amount of unique files = $((${#countUniqFileNames}+1))"

countUniqFileHashes="${uniqFileHashes//[^ ]}"
echo "amount of changes in hashes = $((${#countUniqFileHashes}))"
