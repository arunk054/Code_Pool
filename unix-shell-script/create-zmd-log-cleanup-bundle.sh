#!/bin/sh

echo
echo "This will create a file bundle containing the cron-job to cleanup zmd-messages.log files"
echo

default_value=30
#USAGE
usage()
{
	echo USAGE:
	echo "$0 <Number of days to retain zmd-messages.log files. Zero will never delete. No argument will default to $default_value days>"
        echo 
	echo "$0 --help	will display this message"
        exit 1
}

if [ $# -lt 1 ]
then
	echo "Using default value $default_value days"
	echo ""
	NDays=$default_value
else
	if [[ $1 == "--help" ]]
	then
		usage
	else
		expr $1 + 1 > /dev/null 2>&1 ;
		if (( ($? != 0) || ($1 < 0) ))
		then
			echo "Error: Argument should be zero or greater"
			echo
			usage
		else
			NDays=$1
		fi
	fi
fi

#FIRST create the script
script_file=/tmp/purge-zmd-messages.sh
echo "#!/bin/sh" > $script_file
echo "count=$NDays" >> $script_file
echo "#If the count is 0, then the log files are never deleted" >> $script_file
echo "if [ \$count -le 0 ]" >> $script_file
echo "then" >> $script_file
echo "exit 1" >> $script_file
echo "fi" >> $script_file
echo "logdir=/var/opt/novell/log/zenworks" >> $script_file
echo "if [ -f /etc/SuSE-release ];" >> $script_file
echo "then" >> $script_file
echo "code10=\`grep VERSION /etc/SuSE-release | awk -F \"=\" '{print \$2}' | sed 's/[\t\b ]*//'\`;" >> $script_file
echo "if [ \$code10 == "10" ];" >> $script_file
echo "then" >> $script_file
echo "logdir=/var/log;" >> $script_file
echo "fi" >> $script_file
echo "fi" >> $script_file

echo "find \$logdir -noleaf -maxdepth 1 -name 'zmd-messages.log*' -type f -mtime +\`expr \$count - 1\` -exec rm -f {} \;" >> $script_file
echo "exit 0" >> $script_file



#Second, create the file bundle
bundle=ZMD-cleanup-logs-bundle
bundle_tmp=$bundle-tmp
#Append the number of days to the bundle name, just to know what is the parameter of the cron job
bundle=$bundle-$NDays

if zlman bi $bundle > /dev/null 2>&1 ; then
	echo "Error: The bundle with the name $bundle already exists."
	rm -f $script_file > /dev/null 2>&1
	exit 1
fi

if zlman bi $bundle_tmp > /dev/null 2>&1 ; then
	zlman bd $bundle_tmp > /dev/null 2>&1
fi

zlman fbc $bundle_tmp > /dev/null 2>&1
echo "Successfully created $bundle"

#Next get list of all targets
zlman_tl=/tmp/.zlman.tl
zlman_tl1=/tmp/.zlman.tl.1
zlman tl > $zlman_tl
count=`cat $zlman_tl|wc -l`
count=`expr $count - 3`
tail -$count $zlman_tl > $zlman_tl1
count=`expr $count - 1`
head -$count $zlman_tl1 > $zlman_tl
rm -f $zlman_tl1 > /dev/null 2>&1

#Finally add the file to the bundle for all targets
echo "Adding the cron-job to $bundle for all targets... This might take a few minutes"
i=1
while [ $i -le $count ]
do
	target=`cat $zlman_tl|head -$i|tail -1`
	zlman baf $bundle_tmp $target /etc/cron.daily $script_file --permissions=755 > /dev/null 2>&1
	i=`expr $i + 1`
done
#copy the latest version from tmp bundle to the actual bundle
zlman bco $bundle_tmp `expr $i - 1` $bundle > /dev/null 2>&1

zlman bd $bundle_tmp > /dev/null 2>&1
rm -f $script_file > /dev/null 2>&1
rm -f $zlman_tl > /dev/null 2>&1

echo "Successfully added the cron-job to $bundle"
echo
if [ $NDays -le 0 ]
then
	echo "Assign the bundle $bundle to devices, to NEVER cleanup zmd-messages.log files."
else
	echo "Assign the bundle $bundle to devices, to cleanup zmd-messages.log files older than $NDays days."
fi

exit 0
