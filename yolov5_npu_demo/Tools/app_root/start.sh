#!/bin/sh
while true
do
    if [ "$(ps -ef | grep aidemo | grep -v grep)"x == ""x ];then
        ./aidemo &
    fi
    sleep 30
done