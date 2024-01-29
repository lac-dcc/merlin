#!/usr/bin/env bash

# This script runs Merlin's instrumentation for a given C/C++ input. The program
# is formatted using clang-format before running the actual instrumentation. The
# instrumented program is saved in the output/ directory.
#
# Notice that you must set the variable LLVM_BUILD_DIR to the directory where
# LLVM is built in your computer.
#
# Usage: ./run.sh <input_file> <output_file> <target_function>
#
# Arguments:
#   input_file: Path to the input file.
#   output_file: Name of the output file.
#   target_function: Name of the function that should be instrumented.
#   ignore_non_newton: Indicates whether non-Newton programs should be ignored
#                      for instrumentation.
#   measure_time: Indicates that the instrumentation time should be measured.

function display_usage {
    echo "\
Usage: $0 <input_file> <output_file> <target_function> [-i|--ignore-non-scp] [-m|--measure-time] [-c|--count-non-newton]

Options:
    -i, --ignore-non-scp      Indicates that the function must not be instrumented if it is non-SCP.
    -m, --measure-time        Indicates that Merlin should measure and output instrumentation time.
    -c, --count-non-newton    Indicates that Merlin should count and output the number of Non-Newton Counters.
    -h, --help                Display this help message and exit.\
"
}

LLVM_BUILD_DIR="$HOME/llvm-project/build"
CLANG_FORMAT="$LLVM_BUILD_DIR/bin/clang-format"
LIB="./build/src/libMerlin.so"

POSITIONAL_ARGS=()
OPTIONAL_ARGS=()

# Argument parsing
while [[ $# -gt 0 ]]; do
    case "$1" in
    -i | --ignore-non-scp)
        OPTIONAL_ARGS+=(-Xclang -plugin-arg-merlin -Xclang -ignore-non-scp)
        shift
        ;;
    -m | --measure-time)
        OPTIONAL_ARGS+=(-Xclang -plugin-arg-merlin -Xclang -measure-time)
        shift
        ;;
    -c | --count-non-newton)
        OPTIONAL_ARGS+=(-Xclang -plugin-arg-merlin -Xclang -count-non-newton)
        shift
        ;;
    -h | --help)
        display_usage
        exit 0
        ;;
    -* | --*)
        echo "Invalid option '$1'"
        echo "Use $0 --help for more information."
        exit 1
        ;;
    *)
        POSITIONAL_ARGS+=("$1")
        shift
        ;;
    esac
done

if [ ${#POSITIONAL_ARGS[@]} -lt 3 ]; then
    display_usage
    exit 1
fi

INPUT=${POSITIONAL_ARGS[0]}
OUTPUT=${POSITIONAL_ARGS[1]}
TARGET=${POSITIONAL_ARGS[2]}

FILE=$(basename $INPUT)
EXT="${FILE##*.}"
case $EXT in
"cc" | "cpp") CC="$LLVM_BUILD_DIR/bin/clang++" ;;
"c") CC="$LLVM_BUILD_DIR/bin/clang -std=c99" ;;
esac

mkdir -p output

TEMP=$FILE
$CLANG_FORMAT $INPUT --style="{BasedOnStyle: llvm, InsertBraces: true}" >$TEMP

$CC -fsyntax-only -Xclang -load -Xclang $LIB -Xclang -plugin -Xclang merlin \
    -Xclang -plugin-arg-merlin -Xclang -output-file -Xclang -plugin-arg-merlin -Xclang $OUTPUT \
    -Xclang -plugin-arg-merlin -Xclang -target-function -Xclang -plugin-arg-merlin -Xclang $TARGET \
    "${OPTIONAL_ARGS[@]}" \
    $TEMP

RET_VAL=$?

rm $TEMP

if [ $RET_VAL -ne 0 ]; then
    exit 1
fi

if test -f "output/$OUTPUT"; then
    $CLANG_FORMAT "output/$OUTPUT" -i --style="{BasedOnStyle: llvm}"
fi
