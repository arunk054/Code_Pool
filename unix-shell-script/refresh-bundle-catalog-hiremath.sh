#!/bin/sh

password=novell

# below parts are required for catalog.xml updating as we need to read eDir tree
#ip=164.99.96.37
#tree=IR2_HIREMATH


bundleguid=`psql -dzenworks -Uzenadmin -c "select distinct bundleguid from zen_bundle" | grep -v "bundleguid" | grep -v "-" | grep -v "("`;
for j in $bundleguid
do
	psql -dzenworks -Uzenadmin -c "INSERT INTO zen_queue (qid, action, start_time, entry_time, subject, status, params) VALUES (nextval('hibernate_sequence'), 'Refresh', now(),now(),'com.novell.zenworks.datamodel.extensions.bundles.Bundle|$j', 'N', '')"
done

# This part is for updating catalog.xml file if needed. else remove this part

#cataloguid=`ldapsearch -x -h  $ip -s sub  -b "ou=$tree,o=cell"  -D cn=admin,o=system  -ZZ -p 10389 -w $password  -LLL  nrmObjectType="0#Catalog"   nrmUID  | grep nrmUID  | cut -d " "  -f 2`

#for k in $cataloguid
#do
#	psql -dzenworks -Uzenadmin -c "INSERT INTO zen_queue (qid, action, start_time, entry_time, subject, status, params) VALUES (nextval('hibernate_sequence'), 'Refresh', now(),now(),'com.novell.zenworks.datamodel.extensions.bundles.Catalog|$k', 'N', '')"
#done

