#!/bin/bash

OUTPUT=test
CLEAN="rm -rf $OUTPUT"
COMPILE="\
g++ \
-DWITH_RANDOM_AI \
`pkg-config --cflags gtkmm-3.0` \
src/*.cpp \
`pkg-config --libs gtkmm-3.0` \
-o $OUTPUT\
"

echo You should probably edit this script.

echo Cleaning...
$CLEAN

echo RUN $COMPILE
$COMPILE
echo returns $?
