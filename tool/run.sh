#!/usr/bin/env bash

LIB="./build/src/libMerlin.so"

if [ $# -lt 2 ]
then
    echo 'Syntax: run.sh input_file output_file'
    exit 1
else
    INPUT=$1
    OUTPUT=$2

    FILE=$(basename $INPUT)
    EXT="${FILE##*.}"
    case $EXT in
        "cc" | "cpp") CC="clang++" ;;
        "c") CC="clang" ;;
    esac

    mkdir -p output

    TEMP="temp.${EXT}"
    clang-format $INPUT --style="{BasedOnStyle: llvm, InsertBraces: true}" > $TEMP
    
    $CC -fsyntax-only -Xclang -load -Xclang $LIB -Xclang -plugin -Xclang merlin \
    -Xclang -plugin-arg-merlin  -Xclang -output-file -Xclang -plugin-arg-merlin -Xclang $OUTPUT \
    $TEMP

    rm $TEMP
fi