#!/usr/bin/env bash

if [ $# -lt 3 ]; then
  echo 'Usage: merlin.sh <program_file> <target_function> <input_dir>'
  exit 1
fi

PROGRAM=$1
TARGET=$2
INPUT_DIR=$3
EXT="${PROGRAM##*.}"
OUTPUT="temp.$EXT"
RUN_SCRIPT="./scripts/run.sh"

cd instrumentation
SETUP_OUT=$(./scripts/setup.sh 2>&1)
INST_OUT=$($RUN_SCRIPT "../$PROGRAM" $OUTPUT $TARGET false false)

cd output

case $EXT in
    "cc" | "cpp") CC="clang++" ;;
    "c") CC="clang -std=c99" ;;
esac

$CC $OUTPUT -o temp

TEMP_OUTPUT=""
for i in ../../"$INPUT_DIR"*; 
do 
TEMP_OUTPUT+=$(./temp < "$i")
TEMP_OUTPUT+="\n\nend\n"; done
rm temp*
INPUT_FILE=temp_input.txt
echo -e "$TEMP_OUTPUT" > ../../interpolation/$INPUT_FILE

cd ../../interpolation
MAKE_OUT=$(make 2>&1)

python3 produceInput.py $INPUT_FILE $INPUT_FILE
rm $INPUT_FILE

./bin/interpolator < input/$INPUT_FILE
rm input/$INPUT_FILE