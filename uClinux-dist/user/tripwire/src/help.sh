#!/bin/sh

# $Id: help.sh,v 1.1.1.1 2003/08/18 05:40:12 kaohj Exp $
#
# This file generates 'help.c' from the text in 'help.txt'
#
# Gene Kim
# Purdue University
# May 5, 1993
#

if [ $# -ne 1 ]
then
    echo 'help.sh: run this from the Makefile!'
    exit 1
fi

# print out header of help.c

cat <<EOF
/*
 * help.c
 *
 *	This file was machine-generated by help.sh
 *
 */

#include <stdio.h>

void 
tw_help_print(fp)
    FILE *fp;
{
EOF

# wrap text from help.txt
sed 's/	/\\t/g' < $1 | \
	awk '!/^#/ { printf( "\tfprintf(fp, \"\t%s\\n\");\n", $0); }' 

# footer to help.c
cat <<EOF
}

EOF


