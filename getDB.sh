	#!/bin/bash
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
	echo "StoopidDB is stable!"; 
	fi
	exit 0
