#!/bin/bash

for textfile in test1.txt test2.txt test3.txt
do
	echo -e "TEST file $textfile:"
        ./s21_cat $textfile > s21_cat_output
        cat $textfile > cat_output
        echo -e "$(diff -s cat_output s21_cat_output)\n"
        if [[ $(diff -q ./cat_output ./s21_cat_output) ]]
        then
        echo "____________________________________________________________"
        echo -e "\nFAIL: test failed while testing $textfile\n"
        fi
done


for textfile in test1.txt test2.txt test3.txt
do
	for option in b e n s t v
	do
		echo -e "TEST file $textfile option $option:"
        	./s21_cat -$option $textfile > s21_cat_output
        	cat -$option $textfile > cat_output
        	echo -e "$(diff -s cat_output s21_cat_output)\n"
        	if [[ $(diff -q ./cat_output ./s21_cat_output) ]]
        	then
            	echo "____________________________________________________________"
            	echo -e "\nFAIL: test failed at $option while testing $textfile\n"
        	fi
	done
done

echo -e "TEST files test1.txt test2.txt test3.txt:"
./s21_cat test1.txt test2.txt test3.txt > s21_cat_output
cat test1.txt test2.txt test3.txt > cat_output
echo -e "$(diff -s cat_output s21_cat_output)\n"
if [[ $(diff -q ./cat_output ./s21_cat_output) ]]
then
echo "____________________________________________________________"
echo -e "\nFAIL: test failed while testing multiple files\n"
fi

rm -rf s21_cat_output
rm -rf cat_output
