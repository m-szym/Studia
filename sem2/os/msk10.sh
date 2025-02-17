#!/bin/bash
touch tempp.txt
touch temppp.txt
grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d '"' -f 2,4 | sort -u | cut -d '"' -f 2 | sed "s#.*/##" > tempp.txt
grep -E ' 200 | 206 ' cdlinux.www.log | cut -d " " -f 1,7 | sort -u | cut -d " " -f 2 | sed "s#.*/##" >> tempp.txt
cat tempp.txt | grep ".iso" | sort | uniq -c | sort -nr > temppp.txt
cat temppp.txt
rm tempp.txt
rm temppp.txt
