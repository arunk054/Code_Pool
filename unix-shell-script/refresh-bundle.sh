#!/bin/sh
#script to refresh all bundles in the server
zlman bl -r|grep -v Folder > /tmp/.zlman.bl
count=`cat /tmp/.zlman.bl|wc -l`

#clip the first two lines
count=`expr $count - 2`
cat /tmp/.zlman.bl|tail -$count > /tmp/.zlman.bl

#clip the last line
count=`expr $count - 1`
cat /tmp/.zlman.bl|head -$count > /tmp/.zlman.bl

count=`cat /tmp/.zlman.bl|wc -l`

i=1
while [ $i -le $count ]
do
line=`cat /tmp/.zlman.bl|tail -$i|head -1`
bundle=`echo $line|cut -d '|' -f1`
folder=`echo $line|cut -d '|' -f3`
version=`zlman bi $folder/$bundle|grep Deployed|cut -d '|' -f2`
zlman bp $folder/$bundle $version
i=`expr $i + 1`
done
rm -f /tmp/.zlman.bl
exit 0
