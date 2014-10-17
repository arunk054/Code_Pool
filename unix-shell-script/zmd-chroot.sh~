
if [ `grep 'none /proc proc' /etc/mtab|wc -l` -eq 0 ] ; then
    if [ `ps ax | grep zmd | grep -v grep | grep -v log | wc -l` -gt 0 -a `ps ax | grep zmd.db | grep -v grep | wc -l` -lt 1 ] ; then
        echo "Restarted";
    fi
fi
