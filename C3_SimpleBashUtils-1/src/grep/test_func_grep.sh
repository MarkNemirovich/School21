#!/bin/bash
TEMPLATE_FILE="example.txt"
TEMPLATE_FILE1="test_0_grep.txt"
TEMPLATE_FILE2="test_1_grep.txt"
TEMPLATE_FILE3="test_2_grep.txt"
TEMPLATE_FILE4="test_3_grep.txt"
TEMPLATE_FILE5="test_4_grep.txt"
TEMPLATE_FILE6="test_5_grep.txt"
TEMPLATE_FILE7="test_ptrn_grep.txt"

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s ${TEMPLATE_FILE1} VAR"
"for s21_grep.c s21_grep.h Makefile VAR"
"for s21_grep.c VAR"
"VAR for ^int s21_grep.c s21_grep.h Makefile"
"VAR for ^int s21_grep.c"
"VAR ^print s21_grep.c ${TEMPLATE_FILE7}"
"-e while void s21_grep.c Makefile ${TEMPLATE_FILE7}"
)

declare -a extra=(
"-e '[0-9]' ${TEMPLATE_FILE}"
"-e while -e void s21_grep.c Makefile ${TEMPLATE_FILE7}"
"-e while -e void -e ^int s21_grep.c"
"-n for ${TEMPLATE_FILE2} ${TEMPLATE_FILE3}"
"-n for ${TEMPLATE_FILE1}"
"-e ^int ${TEMPLATE_FILE2}"
"-l for ${TEMPLATE_FILE2} ${TEMPLATE_FILE3}"
"-o int ${TEMPLATE_FILE4}"
"-e out ${TEMPLATE_FILE5}"
"-e ing ${TEMPLATE_FILE6}"
"-c . ${TEMPLATE_FILE2}"
"-l for no_file.txt ${TEMPLATE_FILE3}"
"-f ${TEMPLATE_FILE4} ${TEMPLATE_FILE5}"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
 #     echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
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
