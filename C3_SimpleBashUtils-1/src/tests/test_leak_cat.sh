#!/bin/bash
RED='\033[31m'
GREEN='\033[32m'
BLACK='\033[0m'

FILE1="test_0_grep.txt"
FILE2="test_1_grep.txt"
FILE3="test_2_grep.txt"
FILE4="test_3_grep.txt"
FILE5="test_4_grep.txt"
FILE6="test_5_grep.txt"
FILE7="test_case.txt"
FILE8="test_ptrn.txt"

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR test_case.txt"
)

declare -a extra=(
"-s ${FILE1}.txt"
"-t ${FILE2}.txt"
"-n ${FILE3}.txt"
"-n -b ${FILE4}.txt"
"-s -n -e ${FILE5}.txt"
"-n ${FILE6}.txt"
"-n ${FILE7}.txt ${FILE8}.txt"
"-v ${FILE7}.txt"
"no_file.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    leaks -quiet -atExit -- ./../cat/s21_cat $t > test_s21_cat.log
    leak=$(grep -A100000 leaks test_s21_cat.log)
    (( COUNTER++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
      (( SUCCESS++ ))
        printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $t\n"
    else
      (( FAIL++ ))
        printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $t\n"
    fi
    rm test_s21_cat.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in b e n s t v
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
#for var1 in b e n s t v
#do
#    for var2 in b e n s t v
#    do
#        if [ $var1 != $var2 ]
#        then
#            for i in "${tests[@]}"
#            do
#                var="-$var1 -$var2"
#                testing $i
#            done
#        fi
#    done
#done

# 3 параметра
#for var1 in b e n s t v
#do
#    for var2 in b e n s t v
#    do
#        for var3 in b e n s t v
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1 -$var2 -$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done

# 4 параметра
#for var1 in b e n s t v
#do
#    for var2 in b e n s t v
#    do
#        for var3 in b e n s t v
#        do
#            for var4 in b e n s t v
#            do
#                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
#                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
#                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
#                then
#                    for i in "${tests[@]}"
#                    do
#                        var="-$var1 -$var2 -$var3 -$var4"
#                        testing $i
#                    done
#                fi
#            done
#        done
#    done
#done

printf "\033[31mFAIL: $FAIL\033[0m\n"
printf "\033[32mSUCCESS: $SUCCESS\033[0m\n"
printf "ALL: $COUNTER\n"