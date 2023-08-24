"""Run instrumentation for all benchmarks

This script runs Merlin's instrumentation for all Jotai benchmarks using the 
'run.sh' script. The output for the instrumentation is saved in the 'output/'
directory.

The script reports any errors that occur during the execution of the
instrumentation. It also generates a CSV file that gives the size of the 
function instrumented for each file and wether it was instrumented or not.

Usage:
    python runInstrumentation.py
"""

import pandas as pd
from os import listdir
from subprocess import run

def find_func_name(file_name):
    start = file_name.find('.h_')
    if start == -1:
        start = file_name.find('.c_')
    
    return file_name[start + 3 : -2]

if __name__ == '__main__':
    run('rm -rf output', shell=True)
    benchmark_dir = '../test/jotai_benchmarks'
    inputs = listdir(benchmark_dir)
    print(len(inputs))

    results = []
    errors = []
    for input in inputs:
        print(f'Running: {input}')
        func_target = find_func_name(input) 
        proc = run(
            f'./scripts/run.sh {benchmark_dir}/{input} {input} {func_target}', shell=True, capture_output=True, text=True)

        lines = list(map(lambda x: x.strip(), proc.stdout.split('\n')))
        not_instrumented = len(lines) > 1 and lines[1] == 'Unable to instrument the input'
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
