#! /bin/bash

#script to run a program in simple scalar
# USAGE
usage()
{
	echo
        echo USAGE:
        echo "script to run a program in simple scalar with different parameters."
        echo "Make sure the PATH variable is set for sim-outorder"
        echo
        echo $0 '<'input_file'>' '<'executable'>' '<'Output Stats File'>'
        echo
        echo "Input file contains the format:"
        echo "<config> <v1> <v2> <v3> ... <vn>"
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

inpFile=$1
tmpFile="/tmp/op"
#loop through the file and look for type word

echo "Reading the input file..."

line=`head -1 $inpFile`

config=`echo $line | cut -d ' ' -f1`
j=2
val=`echo $line | cut -d ' ' -f$j`
firstTime="T"
while [ -n "$val" ]
do
    echo "Executing sim-outorder with $config = $val"
    sim-outorder $config $val $2 2>$tmpFile
    echo "Collecting stats..."
    sh parse1.sh $tmpFile $3 $firstTime
    j=`expr $j + 1`
    val=`echo $line | cut -d ' ' -f$j`
    firstTime="F"
    echo ""
done

echo "Done"
exit 0
