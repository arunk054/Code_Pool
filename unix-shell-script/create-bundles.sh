#! /bin/bash

#script to create bundles
# USAGE
usage()
{
        echo USAGE:
        echo "script to create bundles"
        echo $0 '<'bundle-prefix'>' '<'target'>' '<'Number of packages per bundle'>' '<'absolute path of dir of rpms'>'
        echo
        exit 1
}

if [ $# -lt 4 ]
then
usage
fi

bundle_name=$1
target=$2
packages=$3
path=$4


find $path -maxdepth 1 -iname "*rpm"|grep -v "patch.rpm" > /tmp/.zlman.bc
count=`cat /tmp/.zlman.bc|wc -l`
echo "Number of packages found = $count"
i=1
k=1
folder=test-mega-folder
echo "Folder is $folder"
echo ""
zlman bfc $folder
while [ $i -le $count ]
do
zlman bc $bundle_name-$k $folder
j=$i
line=""
while [ $j -lt `expr $i + $packages` ]
do
line="$line `cat /tmp/.zlman.bc|head -$j|tail -1`"
j=`expr $j + 1`
done
echo "Adding Packages - $line"
zlman bap $folder/$bundle_name-$k $target $line
i=`expr $i + $packages`
k=`expr $k + 1`
echo ""
done
