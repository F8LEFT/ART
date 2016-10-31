cd %cd%
if exist tmp.p12 del tmp.p12
if exist PKCS12 del PKCS12
if exist tmp.rsa.pem  del tmp.rsa.pem 
if exist tmp.rsa.pem del tmp.rsa.pem
if exist info.txt del info.txt
if exist cert.x509.pem  del cert.x509.pem 
if exist private.pk8 del private.pk8
if exist private.rsa.pem del private.rsa.pem
keytool   -importkeystore -srckeystore debug.keystore   -destkeystore tmp.p12 -srcstoretype JKS         -deststoretype PKCS12   >>info.txt
openssl  pkcs12 -in tmp.p12 -nodes -out tmp.rsa.pem  >>info.txt
openssl pkcs8 -topk8 -outform DER -in     private.rsa.pem -inform PEM -out private.pk8 -nocrypt  >>info.txt

#info.txt 是用来记录运行过程的
