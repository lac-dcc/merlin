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

# ----------------------- INSTRUMENTATION -----------------------

cd instrumentation

printf "Compiling instrumentation... "
SETUP_OUT=$(./scripts/setup.sh 2>&1)
printf "done\n"

printf "Instrumenting target program... "
INST_OUT=$($RUN_SCRIPT "../$PROGRAM" $OUTPUT $TARGET)
printf "done\n"

cd output

# ----------- COMPILING AND RUNNING THE TARGET PROGRAM -----------

case $EXT in
"cc" | "cpp") CC="clang++" ;;
"c") CC="clang -std=c99" ;;
esac

$CC $OUTPUT -o temp

TEMP_OUTPUT=""
for i in ../../"$INPUT_DIR"*; do
  TEMP_OUTPUT+="$(./temp <"$i")\n"
done

# ------------------------ INTERPOLATION ------------------------

rm temp*
INPUT_FILE=temp_input.txt
echo -e "$TEMP_OUTPUT" >../../interpolation/$INPUT_FILE

cd ../../interpolation
printf "Compiling interpolation... "
MAKE_OUT=$(make 2>&1)
printf "done\n"


python3 produceInput.py $INPUT_FILE $INPUT_FILE
rm $INPUT_FILE

printf "Final output:\n\n"
./bin/interpolator <input/$INPUT_FILE

rm input/$INPUT_FILE
