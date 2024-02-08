#!bin/bash

file=$1

echo $(wc -l < $file)

index=1
unique=1

while IFS= read -r line
do
  prefix=${line%% *} 
  echo $prefix
  unique=1
  for ((i=1;i<=index;i++))
  do
  if [ "$prefix" == "{names[$i]}" ]; then
      unique=0
    fi
    echo "i: $i   ind: $index"
    echo $unique
    echo "$prefix"
    echo "${names[$i]}"
  done
  if [ "$unique" = "1" ]; then
    names[$index]=$prefix
    index=$(($index+1))
    echo $index
  fi
done < "$file"

 
