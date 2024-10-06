#!/bin/bash

randarray () {
	inarray=( $(seq 0 $1) )
	IFS='\n' outarray=($(printf "%s$IFS" "${inarray[@]}" | shuf))
	echo $outarray
}

echo "There are $# args"
echo "$1"

COLS=$(tput cols)
LINES=$(tput lines)
SLEEP=$1

X=0
Y=0
idx=0
declare -a arr
while IFS='\n' read -r line
do
	for ((i=0; i < ${#line}; i++ ));
	do
		printf "char: %q %q %q\n" ${line:i:1} $X $Y
		arr[$((3 * $idx))]=${line:i:1}
		arr[$((3 * $idx + 1))]=$X
		arr[$((3 * $idx + 2))]=$Y
		X=$(($X + 1))
		idx=$(($idx + 1))
	done
	Y=$(($Y + 1))
done

echo ${arr[15]}
echo $idx

clear
tput sc
for i in $(randarray $idx)
do
	tput cup ${arr[$((3 * $i + 2))]} ${arr[$((3 * $i + 1))]}
	printf "%b" ${arr[$((3 * $i))]}
	tput rc
	
done
