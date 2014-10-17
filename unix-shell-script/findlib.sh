find $1 -iname '*.rpm' > /tmp/.findlib
count=`wc -l /tmp/.findlib |cut -d ' ' -f1`
i=1
while [ $i -le $count ]
do
line=`cat /tmp/.findlib|head -$i|tail -1`
rpm -qpl $line|grep $2
if [ $? -eq 0 ]
then
echo $line
rm /tmp/.findlib
exit 0
fi
i=`expr $i + 1`

done
rm /tmp/.findlib
exit 1
