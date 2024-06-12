#!/bin/bash

find="find hamilton"
exit="exit"

for switch in "-h" "-nh"; do
    for (( saturation=30; saturation<=70; saturation=saturation+40 )); do
        for (( nNodes=1; nNodes<=15; nNodes++ )); do
./exe/main.exe "$switch" << EOF
$nNodes
$saturation
$find
$exit
EOF
        done

        for (( nNodes=20; nNodes<=100; nNodes=nNodes+10 )); do
./exe/main.exe "$switch" << EOF
$nNodes
$saturation
$exit
EOF
        done

        for (( nNodes=200; nNodes<=500; nNodes=nNodes+100 )); do
./exe/main.exe "$switch" << EOF
$nNodes
$saturation
$exit
EOF
        done

        nNodes = 1000

./exe/main.exe "$switch" << EOF
$nNodes
$saturation
$exit
EOF
    done
done    
