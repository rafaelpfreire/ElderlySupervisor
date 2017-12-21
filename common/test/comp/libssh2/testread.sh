#!/bin/bash

mode=r
ip=10.121.3.13
usr=fredy
pbKey=/home/rafael/.ssh/id_rsa.pub
prKey=/home/rafael/.ssh/id_rsa
from=/home/fredy/rafael/teste.txt
to=/home/rafael/ElderlySupervisor/teste.txt

if [ -f $to ]; then
    rm $to
fi

./bin/scp $mode $ip $usr $pbKey $prKey $from $to

if [ $? -eq 0 ]; then
    if [ -f $to ]; then
        echo "[OK] Test was successfuly executed!"
    else
        echo "[NOK] Test failed!"
    fi
else
    echo "[NOK] Test failed!"
fi
