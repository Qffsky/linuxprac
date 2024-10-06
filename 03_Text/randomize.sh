#!/bin/bash

randarray () {
	inarray=( $(seq 0 $1) )
	IFS='\n' outarray=($(printf "%s$IFS" "${inarray[@]}" | shuf))
	echo $outarray
}

addchar () {
	arr[$((3 * $1))]=$4
        arr[$((3 * $1 + 1))]=$2
     	arr[$((3 * $1 + 2))]=$3
}

COLS=$(tput cols)
LINES=$(tput lines)
SLEEP=$1

Y=0
idx=0
declare -a arr
while IFS='\n' read -r line
do
	X=0
	for ((i=0; i < ${#line}; i++ ));
	do
		case ${line:i:1} in
			' ')
				;;
			*)
				addchar $idx $X $Y ${line:i:1}
				;;
		esac
		X=$(($X + 1))
		idx=$(($idx + 1))
	done
	Y=$(($Y + 1))
done

clear
for i in $(randarray $idx)
do
	tput home
	tput cup ${arr[$((3 * $i + 2))]} ${arr[$((3 * $i + 1))]}
	sleep ${SLEEP:-0}
	printf "%b" ${arr[$((3 * $i))]}
	#echo ${arr[$((3 * $i))]}
	
done

tput cup $LINES 0
