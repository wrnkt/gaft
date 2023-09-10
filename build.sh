#!/bin/bash

if [ "$1" == "console" ]
    then
    g++-13 -std=c++20 -ggdb \
        ./src/console.cpp \
        ./src/metadata_processor.cpp \
        ./src/session.cpp \
        -o ./bin/gaft-console -lsqlite3
elif [ "$1" == "ui" ]
then
    g++-13 -std=c++20 -ggdb \
        ./src/main.cpp \
        ./src/metadata_processor.cpp \
        -o ./bin/gaft -lsqlite3
fi
exit 0
