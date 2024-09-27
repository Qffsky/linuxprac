#!/bin/sh

REFERENCE=$1
PROG=$2
PROG_A=$3
PROG_SO=$4

if cmp -s "$REFERENCE" "$PROG"
then
   echo "prog...........YES"
else
   echo "prog...........NO"
fi

if cmp -s "$REFERENCE" "$PROG_A"
then
   echo "prog-a.........YES"
else
   echo "prog-a.........NO"
fi

if cmp -s "$REFERENCE" "$PROG_SO"
then
   echo "prog-so........YES"
else
   echo "prog-so........NO"
fi


