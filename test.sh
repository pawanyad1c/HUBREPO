#!/bin/bash
#if ( make -j4 )
#then
#chmod 777 /dev/ttyUSB3 &
#cd  /home/bitcomm/chander/till17-sep/
cd /home/bitcomm/chander/smsBIN/
sudo ./sms_service &
#tail -f ./SMS_SENDER/log/sms_log.txt 
#fi
