#!/bin/bash

for textfile in grep_test1.txt grep_test2.txt grep_test3.txt
do
	for template in linux MacOS macos grep tennis sky
	do
		echo -e "TEST file $textfile with template $template:"
		./s21_grep $template $textfile > s21_grep_output
		grep $template $textfile > grep_output
		echo -e "$(diff -s grep_output s21_grep_output)\n"
		if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
		then
		echo "____________________________________________________________"
		echo -e "\nFAIL: test failed while testing $textfile with template $template\n"
        fi
	done
done

for textfile in grep_test1.txt grep_test2.txt grep_test3.txt
do
	for template in linux MacOS macos grep tennis sky
	do
		for option in i v c l n h s
		do
			echo "leaks -atExit --  ./s21_grep -$option $template $textfile"
			echo -e "TEST file $textfile with option $option:"
			./s21_grep -$option $template $textfile > s21_grep_output
			grep -$option $template $textfile > grep_output
			echo -e "$(diff -s grep_output s21_grep_output)\n"
			if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
			then
			echo "____________________________________________________________"
			echo -e "\nFAIL: test failed at $option while testing $textfile with template $template\n"
			fi
		done
	done
done

for textfile in grep_test1.txt grep_test2.txt grep_test3.txt
do
	for template in linux MacOS macos grep tennis sky
	do
		for option in i v c l n h s
		do
			for second_option in i v n h s
			do
				echo "leaks -atExit --  ./s21_grep -$option $template $textfile"
				echo -e "TEST file $textfile with option $option and second option $second_option:"
				./s21_grep -$option -$second_option $template $textfile > s21_grep_output
				grep -$option -$second_option $template $textfile > grep_output
				echo -e "$(diff -s grep_output s21_grep_output)\n"
				if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
				then
				echo "____________________________________________________________"
				echo -e "\nFAIL: test failed at $option while testing $textfile with template $template\n"
				echo "grep -$option -$second_option $template $textfile > grep_output"
				fi
			done
		done
	done
done

echo -e "TEST multiple files with multiple templates including templates from files:"
./s21_grep -e tennis -e macos -e grep_test3.txt -f pattern_file1.txt -f pattern_file2.txt grep_test1.txt grep_test2.txt grep_test3.txt > s21_grep_output
grep -e tennis -e macos -e linux -f pattern_file1.txt -f pattern_file2.txt grep_test1.txt grep_test2.txt grep_test3.txt > grep_output
echo -e "$(diff -s grep_output s21_grep_output)\n"
if [[ $(diff -q ./grep_output ./s21_grep_output) ]]
then
echo "____________________________________________________________"
echo -e "\nFAIL: test failed while testing multiple files\n"
fi	

rm -rf s21_grep_output
rm -rf grep_output
