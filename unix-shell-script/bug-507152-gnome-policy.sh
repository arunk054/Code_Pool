if [ ! -f /usr/share/zmd/SOAP/PolicyManager.asmx.backup ]; then
	cp /usr/share/zmd/SOAP/PolicyManager.asmx /usr/share/zmd/SOAP/PolicyManager.asmx.backup
fi
echo "<%@ WebService Language=\"c#\" Class=\"Novell.Zenworks.PolicyManager.PolicyManager, Novell.Zenworks.PolicyManager, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null\" %>" > /usr/share/zmd/SOAP/PolicyManager.asmx
