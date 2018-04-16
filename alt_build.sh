#!/bin/bash

CMD="\
g++ \
-DWITH_RANDOM_AI \
`pkg-config --cflags gtkmm-3.0` \
src/*.cpp \
`pkg-config --libs gtkmm-3.0` \
-o test\
"

echo You should probably edit this script.
echo RUN $CMD
echo

$CMD
