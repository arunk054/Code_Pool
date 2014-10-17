#! /bin/bash

# script to extract the stats for a given config from the stats file
# USAGE
usage()
{
	echo
        echo USAGE:
        echo "script to extract the stats for a given config from the stats file."
        echo $0 '<'config_name'>' '<'Input Stats File'>'
        echo
        exit 1
}


if [ "$1" == "--help" ]
then
usage
fi

if [ $# -lt 2 ]
then
usage
fi

statsFile=$2

echo "Reading the stats file..."

#loop through the file and look for the given
count=`wc -l $statsFile |cut -d ' ' -f1`
i=1

while [ $i -le $count ]
do

line=`head -$i $statsFile|tail -1`
echo $line | grep $1 1>/dev/null

if [ $? -eq 0 ]
then

    echo "Found the requested config."
    echo "Following is the stats:"
    echo""    
    echo "--------------------"
    echo $1
    echo "--------------------"

    j=2
    val=`echo $line | cut -d '|' -f$j`
    while [ -n "$val" ]
    do
        echo $val
        j=`expr $j + 1`
        val=`echo $line | cut -d '|' -f$j`
    done
    i=$count
fi
i=`expr $i + 1`
done

echo ""
exit 0
