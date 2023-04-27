#!/usr/bin/env bash

LIB="./build/src/libMerlin.so"

if [ $# -lt 2 ]
then
    echo 'Syntax: run input_file output_file'
    exit 1
else
    INPUT=$1
    OUTPUT=$2

    mkdir -p output

    clang++ -stdlib=libc++ -fsyntax-only -Xclang -load -Xclang $LIB -Xclang -plugin -Xclang merlin \
    -Xclang -plugin-arg-merlin  -Xclang -output-file -Xclang -plugin-arg-merlin -Xclang $OUTPUT \
    $INPUT
fi