"""Run instrumentation for all benchmarks and measure execution time

This script runs Merlin's instrumentation for all Jotai benchmarks using the 
'run.sh' script and measures both the total execution time and the time required
only for instrumentation.

The instrumentation is run four times and the first run is discarded. The script
outputs the average times for the other three runs.

Usage:
    python measureTime.py
"""

from os import listdir, remove
from subprocess import run

import pandas as pd

from find_func_name import find_func_name

TEMP_FILE = 'total_time.tmp'
NUM_RUNS = 3


def run_program(program, results):
    ignore_non_newton = 'false'
    measure_time = 'true'
    func_target = find_func_name(program)

    command = f'./scripts/run.sh \
{benchmark_dir}/{program} {program} {func_target} {ignore_non_newton} {measure_time}'
    run(command, shell=True, capture_output=True, text=True)

    # Clear the contents of the temp file
    open(TEMP_FILE, 'w').close()

    command = f'/usr/bin/time -f %e -a -o {TEMP_FILE} ./scripts/run.sh \
{benchmark_dir}/{program} {program} {func_target} {ignore_non_newton} {measure_time}'

    times = []
    for _ in range(NUM_RUNS):
        proc = run(command, shell=True, capture_output=True, text=True)

        lines = list(map(lambda x: x.strip(), proc.stdout.split('\n')))
        size = int(lines[0])
        times.append(int(lines[1]))

    avg_instrumentation_time_micro = sum(times) / NUM_RUNS

    with open(TEMP_FILE, 'r') as file:
        times = file.readlines()
        avg_total_time = sum(map(lambda x: float(x), times)) / NUM_RUNS

    results.append({'program': program, 'inst_time': avg_instrumentation_time_micro,
                    'total_time': avg_total_time, 'ast_size': size})


if __name__ == '__main__':
    benchmark_dir = '../test/jotai_benchmarks'
    inputs = listdir(benchmark_dir)

    instrumentation_times = []
    total_times = []

    results = []

    for input in inputs:
        run_program(input, results)

    remove(TEMP_FILE)

    df = pd.DataFrame(data=results, columns=results[0].keys())
    df.to_csv('./exp_RQ5.csv', mode='w', header=True, index=False)

    with open('./exp_RQ5.txt', mode='w') as file:
        avg_instrumentation_time_milli = df['inst_time'].sum() / 1000
        avg_total_time = df['total_time'].sum()

        file.write(
            f'Average Instrumentation Time: {avg_instrumentation_time_milli:.3f}ms\n')
        file.write(f'Average Total Processing Time: {avg_total_time:.3f}s\n')
