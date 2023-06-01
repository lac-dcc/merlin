#!/usr/bin/env bash

if [ $# -lt 2 ]
then
    echo 'Syntax: run.sh input_file output_file'
    exit 1
else
    LLVM_BUILD_DIR="$HOME/llvm-project/build"
    CLANG_FORMAT="$LLVM_BUILD_DIR/bin/clang-format"
    LIB="./build/src/libMerlin.so"
    INPUT=$1
    OUTPUT=$2

    FILE=$(basename $INPUT)
    EXT="${FILE##*.}"
    case $EXT in
        "cc" | "cpp") CC="clang++" ;;
        "c") CC="clang" ;;
    esac

    mkdir -p output

    TEMP=$FILE
    $CLANG_FORMAT $INPUT --style="{BasedOnStyle: llvm, InsertBraces: true}" > $TEMP
    
    $CC -std=c99 -fsyntax-only -Xclang -load -Xclang $LIB -Xclang -plugin -Xclang merlin \
    -Xclang -plugin-arg-merlin  -Xclang -output-file -Xclang -plugin-arg-merlin -Xclang $OUTPUT \
    $TEMP

    rm $TEMP

    if test -f "output/$OUTPUT"; then
        $CLANG_FORMAT "output/$OUTPUT" -i --style="{BasedOnStyle: llvm}" 
    fi
fi