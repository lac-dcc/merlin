#!/usr/bin/env bash

if [ $# -lt 2 ]; then
  echo 'Usage: merlin.sh <program_file> <target_function>'
  exit 1
fi

PROGRAM=$1
TARGET=$2
EXT="${PROGRAM##*.}"
OUTPUT="temp.$EXT"
RUN_SCRIPT="./scripts/run.sh"
TIME_FLAG="--measure-time"
TEMP_INST_FILE="$(pwd)/inst.time"
TEMP_INTERP_FILE="$(pwd)/interp.time"

# ----------------------- INSTRUMENTATION -----------------------

printf "Instrumenting target program... "
$RUN_SCRIPT $TIME_FLAG $PROGRAM $OUTPUT $TARGET > $TEMP_INST_FILE
printf "done\n"

cd output

# ----------- COMPILING AND RUNNING THE TARGET PROGRAM -----------

case $EXT in
"cc" | "cpp") CC="clang++" ;;
"c") CC="clang -std=c99" ;;
esac

$CC $OUTPUT -o temp

TEMP_OUTPUT=""
for entry in {0..4}; do
  out=$(./temp "$entry")

  if [[ $(echo "$out" | head -n 1 | xargs) == "Usage:" ]]; then
    break
  fi

  TEMP_OUTPUT+="$out\n"
done

# ------------------------ INTERPOLATION ------------------------

# rm temp*
INPUT_FILE=temp_input.txt
echo -e "$TEMP_OUTPUT" >../../interpolation/$INPUT_FILE


cd ../../interpolation

cat $INPUT_FILE
python3 produceInput.py $INPUT_FILE $INPUT_FILE
# rm $INPUT_FILE

# printf "Final output:\n\n"
# ./bin/interpolator $TIME_FLAG <input/$INPUT_FILE 2> $TEMP_INTERP_FILE

# rm input/$INPUT_FILE
