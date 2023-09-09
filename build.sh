#!/bin/bash
g++-13 -std=c++20 src/main.cpp ./src/metadata_processor.cpp -o ./bin/main -lsqlite3
exit 0
