#! /bin/bash

#script to parse the output of the sim-outorder execution
# USAGE
usage()
{
	echo
        echo USAGE:
        echo "script to parse the output of sim-outorder execution"
        echo $0 '<'output_file'>' '<'stats_file'>' '<'First_time'>'
        echo
        exit 1
}

if [ "$1" == "--help" ]
then
usage
fi

if [ $# -lt 3 ]
then
usage
fi

tmpFile=$1
statsFile=$2
tmpStatsFile="/tmp/st"
rm -rf $tmpStatsFile 2>/dev/null

#loop through the file and look for the first config
count=`wc -l $tmpFile |cut -d ' ' -f1`
i=1
echo "Parsing the output..."
while [ $i -le $count ]
do
#Read each line and look for the start of the stats
line=`head -$i $tmpFile|tail -1`
echo $line | grep "sim_num_insn"  1>/dev/null

if [ $? -eq 0 ]
then
    k=1
    while [ $i -le $count ]
    do

        #store the stats
        if [ -n "$line" ]
        then
            config=`echo $line|cut -d ' ' -f1`
            j=2
            val=`echo $line|cut -d ' ' -f$j`
            while [ ! -n "$val" ]
            do
                val=`echo $line|cut -d ' ' -f$j`
            done

            # Read the stats file, only if not first time
            if [ "$3" == "T" ]
            then
                config=$config"|"$val
                echo $config >> $tmpStatsFile
            else
                sline=`head -$k $statsFile|tail -1`
                sline=$sline"|"$val       
                echo $sline >> $tmpStatsFile     
                k=`expr $k + 1`
            fi
        fi

        i=`expr $i + 1`
        line=`head -$i $tmpFile|tail -1`
    done
fi

i=`expr $i + 1`
done
cp $tmpStatsFile $statsFile
echo "Done"
exit 0
