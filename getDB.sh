#!/bin/bash
if [ "$3" == "1" ]
	then
    TAG="$(curl --silent https://api.github.com/repos/AnzoDK/StoopidDB/tags | jq -r '.[0].name')"
    curl -L https://github.com/AnzoDK/StoopidDB/archive/refs/tags/$TAG.zip -o ./stoopidZip.zip
    if [ $? -ne 0 ]
    then
        echo "Git clone error"
        exit 1
    fi
    DIR="$(unzip -l ./stoopidZip.zip | grep "StoopidDB" | head -1)"
    echo "$DIR"
    REAL_DIR=""
    for (( i=0; i<${#DIR}; i++ ))
    do
        TEST="${DIR:$i:1}"
        echo "Testing $TEST"
        if [ "$TEST" == "S" ]
        then
            REAL_DIR="${DIR:$i}"
            break
        fi
    done
    unzip ./stoopidZip.zip
    echo "REAL DIR: $REAL_DIR"
    cd $REAL_DIR
    ls
    ./INSTALL-Dev.sh
    cd ..
    rm -rf $REAL_DIR
    rm ./stoopidZip.zip
fi
git clone https://github.com/AnzoDK/StoopidDB
if [ $? -ne 0 ]
then
       echo "Git clone error"
       exit 1
fi
cd StoopidDB
git checkout dev
if [ "$1" == "--debug" ]
then
    make -f ./makefile release
else
    make -f ./makefile optimize
fi
./test.out
if [ $? -ne 0 ]
then 
    echo "Unstable StoopidDB Release! Errored out" 
    exit 1
else 
    echo "StoopidDB is stable!"
fi
exit 0

