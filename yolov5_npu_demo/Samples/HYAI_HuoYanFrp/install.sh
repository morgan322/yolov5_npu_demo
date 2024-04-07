#!/bin/sh
while true
do
    if [ "$(ps -ef | grep frpc | grep -v grep)"x == ""x ];then
        ./frpc -c ./frpc.ini &
    fi
    sleep 30
done