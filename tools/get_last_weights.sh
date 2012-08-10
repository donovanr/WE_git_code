#!/bin/bash

cat $1 | sed -n 'H; /^snapshot/h; ${g;p;}' | awk '{ if( NR > 2 ) { print } }' | awk '{split($1,a,"="); split($3,b,"="); split($4,c,"="); print a[2] "\t" b[2] "\t" c[2]}' | awk '{ sum[$2] += $3; } END { for (i in sum) print i "\t" sum[i] }' | awk -F'\t' '$1!=""' | sort -n