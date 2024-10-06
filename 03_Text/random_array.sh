#!/bin/bash

randarray () {
inarray=( $(seq 1 $1) )
IFS='\n' outarray=($(printf "%s$IFS" "${inarray[@]}" | shuf))
echo $outarray
}

randarray 10
