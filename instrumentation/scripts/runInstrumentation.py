"""Run instrumentation for all benchmarks

This script runs Merlin's instrumentation for all Jotai benchmarks in a given
directory using the 'run.sh' script. The output for the instrumentation is saved
in the 'output/' directory.

The script reports any errors that occur during the execution of the
instrumentation. It also generates a CSV file that gives the size of the 
function instrumented for each file and wether it was instrumented or not.

Usage:
    python runInstrumentation.py <directory>

Arguments:
    directory (str): Path to the directory with the programs to be instrumented.
"""

import pandas as pd
from os import listdir
from subprocess import run
from sys import argv, stderr

from find_func_name import find_func_name

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: python {argv[0]} <directory>', file=stderr)
        exit(1)

    run('rm -rf output', shell=True)
    dir_name = argv[1]
    inputs = listdir(dir_name)
    ignore_non_newton = 'false'
    measure_time = 'false'
    print(len(inputs))

    results = []
    errors = []
    for input in inputs:
        print(f'Running: {input}')
        func_target = find_func_name(input)
        proc = run(f'./scripts/run.sh \
{dir_name}/{input} {input} {func_target} {ignore_non_newton} {measure_time}',
                   shell=True, capture_output=True, text=True)

        lines = list(map(lambda x: x.strip(), proc.stdout.split('\n')))
        not_instrumented = len(
            lines) > 1 and lines[1] == 'Unable to instrument the input'
        results.append({
            'name': input,
            'func_size': int(lines[0]),
            'instrumented': not not_instrumented
        })

        if proc.returncode != 0:
            errors.append((input, proc.stderr))

    if len(errors) > 0:
        print('\n\n======================ERRORS======================\n\n')
        for (input, err) in errors:
            print(f'======================{input}======================')
            print(err)

    columns = ['name', 'func_size', 'instrumented']
    df = pd.DataFrame(data=results, columns=columns)
    df.to_csv('experimentRQ1.csv', mode='w', header=True, index=False)
