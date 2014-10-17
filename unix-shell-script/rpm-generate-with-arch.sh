#! /bin/bash

#script to generate test rpms
# USAGE
usage()
{
        echo USAGE:
        echo "script to generate test rpms"
        echo $0 '<'rpmName'>' '<'no of rpms'>' '<'absolute path of file or dir to be packaged'>'
        echo
        exit 1
}

rpm_name=$1
echo $2 | grep "^[0-9]*$"
if [ $? -ne 0 ]
then
usage
fi
count=$2
file=$3

if [ $# -lt 3 ]
then
usage
fi

i=1
while [ $i -le $count ]
do
build_root=/usr/src/packages/BUILD/akalyan-test-root
file_dir=$build_root`dirname $file`
mkdir -p $file_dir
spec_file=/tmp/${rpm_name}.spec
rm $spec_file > /dev/null 2>&1
echo 'Summary: AKALYAN Test rpm' >> $spec_file
echo 'Name: '${rpm_name} >> $spec_file
echo 'Version: 2.0.0'  >> $spec_file
echo 'Release: 1' >> $spec_file
echo 'License: GPL' >> $spec_file
echo 'Group: Development/Tools' >> $spec_file
echo 'BuildArch: i686' >> $spec_file
echo 'Requires: /bin/ls' >> $spec_file
echo 'Provides: '${rpm_name} >> $spec_file
echo '%description' >> $spec_file
echo 'This is a test rpm built for testing by arun kalyanasundaram' >> $spec_file
echo '%setup' >> $spec_file
echo '%build' >> $spec_file
#we copy the file to the build root
echo 'cp -r '$file $file_dir >> $spec_file
echo '%files' >> $spec_file
echo '%defattr(-,root,root)' >> $spec_file
echo $file >> $spec_file
rpmbuild --quiet -bb $spec_file
#clean the build_root, spec file
rm -rf $build_root
#rm $spec_file
i=`expr $i + 1`
done
