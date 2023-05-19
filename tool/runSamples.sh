#!/usr/bin/env bash

for INPUT in ../test/sample*
do
  OUTPUT=$(basename $INPUT)
  ./run.sh $INPUT $OUTPUT
done