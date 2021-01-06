#!/bin/sh
export C_INCLUDE_PATH=$C_INCLUDE_PATH:./include
export LIBRARY_PATH=$LIBRARY_PATH:./lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
make example

