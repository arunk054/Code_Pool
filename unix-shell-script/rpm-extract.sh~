#! /bin/bash

#script to extract rpm
# USAGE
usage()
{
        echo USAGE:
        echo "script to copy files of an installed rpm to a destination directory in the same structure"
        echo $0 '<'rpm name'>' '<'absolute path of destination directory'>'
        echo
        exit 1
}

if [ $# -lt 2 ]
then
usage
fi

rpm_name=$1
dest=$2
mkdir -p $dest
temp_file=/tmp/.extract.zlm
rpm -ql $rpm_name > $temp_file
count=`cat $temp_file|wc -l`
echo ""
echo "=========================================================================="
echo "Number of files found = $count"

i=1
dir=0
files=0

while [ $i -le $count ]
do
line=`cat $temp_file|head -$i|tail -1`

if [ -d $line ]
then
dir=`expr $dir + 1`
mkdir -p $dest/$line
else
file=`expr $file + 1`
mkdir -p $dest/$line
rm -r $dest/$line
cp $line $dest/$line
fi

i=`expr $i + 1`
done

echo "number of directoriess created = $dir"
echo "number of files created = $file"
echo ""
echo "rpm files extracted at $dest" 
echo "=========================================================================="
rm $temp_file
