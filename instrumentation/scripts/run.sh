#!/usr/bin/env bash

# This script runs Merlin's instrumentation for a given C/C++ input. The program
# is formatted using clang-format before running the actual instrumentation. The
# instrumented program is saved in the output/ directory.
# 
# Notice that you must set the variable LLVM_BUILD_DIR to the directory where
# LLVM is built in your computer.
#
# Usage: ./run.sh <input_file> <output_file>
#
# Arguments: 
#   input_file: Path to the input file.
#   output_file: Name of the output file.

if [ $# -lt 2 ]; then
    echo 'Usage: run.sh <input_file> <output_file>'
    exit 1
fi

LLVM_BUILD_DIR="$HOME/llvm-project/build"
CLANG_FORMAT="$LLVM_BUILD_DIR/bin/clang-format"
LIB="./build/src/libMerlin.so"
INPUT=$1
OUTPUT=$2

FILE=$(basename $INPUT)
EXT="${FILE##*.}"
case $EXT in
    "cc" | "cpp") CC="$LLVM_BUILD_DIR/bin/clang++" ;;
    "c") CC="$LLVM_BUILD_DIR/bin/clang" ;;
esac

mkdir -p output

TEMP=$FILE
$CLANG_FORMAT $INPUT --style="{BasedOnStyle: llvm, InsertBraces: true}" > $TEMP

$CC -std=c99 -fsyntax-only -Xclang -load -Xclang $LIB -Xclang -plugin -Xclang merlin \
-Xclang -plugin-arg-merlin  -Xclang -output-file -Xclang -plugin-arg-merlin -Xclang $OUTPUT \
$TEMP

RET_VAL=$?

rm $TEMP

if [ $RET_VAL -ne 0 ]; then
    exit 1
fi

if test -f "output/$OUTPUT"; then
    $CLANG_FORMAT "output/$OUTPUT" -i --style="{BasedOnStyle: llvm}" 
fi