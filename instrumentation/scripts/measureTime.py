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

from find_func_name import find_func_name


def run_instrumentation_and_measure_time(inputs):
    temp_file = 'total_time.tmp'
    ignore_non_newton = 'false'
    measure_time = 'true'

    times = []
    for input in inputs:
        func_target = find_func_name(input)

        command = f'/usr/bin/time -f %e -a -o {temp_file} ./scripts/run.sh \
{benchmark_dir}/{input} {input} {func_target} {ignore_non_newton} {measure_time}'
        proc = run(command, shell=True, capture_output=True, text=True)

        lines = list(map(lambda x: x.strip(), proc.stdout.split('\n')))
        times.append(int(lines[2]))

    instrumentation_time_micro = sum(times)

    with open(temp_file, 'r') as file:
        times = file.readlines()
        total_time = sum(map(lambda x: float(x), times))

    remove(temp_file)

    return instrumentation_time_micro, total_time


if __name__ == '__main__':
    benchmark_dir = '../test/jotai_benchmarks'
    inputs = listdir(benchmark_dir)

    instrumentation_times = []
    total_times = []

    run_instrumentation_and_measure_time(inputs)
    for _ in range(3):
        instrumentation_time_micro, total_time = run_instrumentation_and_measure_time(
            inputs)
        instrumentation_times.append(instrumentation_time_micro)
        total_times.append(total_time)

    avg_instrumentation_time_milli = (
        sum(instrumentation_times) / len(instrumentation_times)) / 1000
    avg_total_time = sum(total_times) / len(total_times)

    with open('exp_RQ5.txt', mode='w') as file:
        file.write(
            f'Average Instrumentation Time: {avg_instrumentation_time_milli:.3f}ms\n')
        file.write(f'Average Total Processing Time: {avg_total_time:.3f}s')
