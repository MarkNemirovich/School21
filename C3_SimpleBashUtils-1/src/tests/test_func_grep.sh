#!/bin/bash
FILE1="test_0.txt"
FILE2="test_1.txt"
FILE3="test_2.txt"
FILE4="test_3.txt"
FILE5="test_4.txt"
FILE6="test_5.txt"
FILE7="test_case.txt"
FILE8="test_ptrn.txt"

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"ss ${FILE1} VAR"
"for ${FILE2} ${FILE3} VAR"
"for ${FILE4} VAR"
"VAR for ^int ${FILE4} ${FILE5} ${FILE6}"
"VAR for ^int ${FILE5}"
"VAR ^print s21_grep.c ${FILE7}"
"-e while void s21_grep.c Makefile ${FILE8}"
)

declare -a extra=(
"-e '[0-9]' ${FILE1}"
"-e while -e void ${FILE4} ${FILE5} ${FILE6}"
"-e while -e void -e ^int ${FILE5}"
"-n for ${FILE2} ${FILE3}"
"-n for ${FILE1}"
"-e ^int ${FILE2}"
"-l for ${FILE2} ${FILE3}"
"-o int ${FILE4}"
"-e out ${FILE5}"
"-e ing ${FILE6}"
"-c . ${FILE2}"
"-l for no_file.txt ${FILE3}"
"-f ${FILE7} ${FILE8}"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./../grep/s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t\n"
    else
      (( FAIL++ ))
      printf "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t\n"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

# ## специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
# c l n h o i s
for var1 in v c l n h o i s
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 сдвоенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

# 3 строенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $i
                done
            fi
        done
    done
done

echo -e "\033[31mFAIL: $FAIL\033[0m"
echo -e "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"
