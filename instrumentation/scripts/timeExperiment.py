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
from subprocess import run, DEVNULL

from find_func_name import find_func_name

import pandas as pd

INST_TIME_FILE='inst.time'
INTERP_TIME_FILE='interp.time'
TEMP_FILE = 'total_time.tmp'
NUM_RUNS = 3


def run_program(program, results):
    func_target = find_func_name(program)

    # First run is discarded
    command = f'/usr/bin/time -f %e -a -o {TEMP_FILE} ./scripts/time-experiment.sh {program} {func_target}'
    run(command, shell=True, text=True, stdout=DEVNULL, stderr=DEVNULL)

    # Clear the contents of the temp file
    open(TEMP_FILE, 'w').close()

    inst_times = []
    interp_times = []
    for _ in range(NUM_RUNS):
        run(command, shell=True, text=True, stdout=DEVNULL, stderr=DEVNULL)

        with open(INST_TIME_FILE, 'r') as file:    
            lines = list(map(lambda x: x.strip(), file.readlines()))
            size = int(lines[0].split(': ')[1])
            inst_times.append(int(lines[1].split(': ')[1][:-2]))

        with open(INTERP_TIME_FILE, 'r') as file:    
            lines = list(map(lambda x: x.strip(), file.readlines()))
            interp_times.append(int(lines[0].split(': ')[1][:-2]))

    avg_instrumentation_time_micro = sum(inst_times) / NUM_RUNS
    avg_interpolation_time_micro = sum(interp_times) / NUM_RUNS

    with open(TEMP_FILE, 'r') as file:
        total_times = file.readlines()
        avg_total_time = sum(map(lambda x: float(x), total_times)) / NUM_RUNS

    results.append({'program': program,
                    'inst_time': avg_instrumentation_time_micro,
                    'interp_time': avg_interpolation_time_micro,
                    'total_time': avg_total_time, 'ast_size': size})


if __name__ == '__main__':
    benchmark_dir = '../test/jotai_benchmarks'
    inputs = listdir(benchmark_dir)

    interpolation_times = []
    total_times = []

    results = []

    for input in inputs:
        print(f'Running Program: {benchmark_dir}/{input} ...')
        run_program(f'{benchmark_dir}/{input}', results)

    remove(TEMP_FILE)
    remove(INST_TIME_FILE)
    remove(INTERP_TIME_FILE)

    df = pd.DataFrame(data=results, columns=results[0].keys())
    df.to_csv('./exp_RQ5.csv', mode='w', header=True, index=False)

    with open('./exp_RQ5.txt', mode='w') as file:
        avg_instrumentation_time_milli = df['inst_time'].sum() / 1000
        avg_interpolation_time_milli = df['iterp_time'].sum() / 1000
        avg_total_time = df['total_time'].sum()

        file.write(f'Average Instrumentation Time: {avg_instrumentation_time_milli:.3f}ms\n')
        file.write(f'Average Interpolation Time: {avg_interpolation_time_milli:.3f}ms\n')
        file.write(f'Average Total Processing Time: {avg_total_time:.3f}s\n')
