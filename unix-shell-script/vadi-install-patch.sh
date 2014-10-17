#!/bin/sh

if [ -z $1 ];
then
    echo "Usage ./patch.sh <breakout mount point>";
    exit -1;
fi
mkdir data;
ln -f -s $1/readmes readmes;
ln -f -s $1/data/eulas data/eulas;
ln -f -s $1/data/packages data/packages;
ln -f -s $1/data/locale data/locale;
mkdir -p data/configureScripts
cp $1/* . ;
cp $1/data/* data/ ;
cp $1/data/configureScripts/* data/configureScripts/ ;

echo "Patching upgrade script Complete..";
echo "Execute zlm-upgrade now from this directory"


