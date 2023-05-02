#!/usr/bin/env bash

for INPUT in ../test/jotai_benchmarks/*
do
  OUTPUT=$(basename $INPUT)
  ./run.sh $INPUT $OUTPUT
done