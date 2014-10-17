path="http://dist.suse.de/full/full-sle11-x86_64/suse/x86_64/"
arg=" "
while [ "$*" != "" ]
do
    arg=${arg}$path$1".rpm "
  shift
done

echo 'executing command: rpm -Uvh '$arg
rpm -Uvh $arg
