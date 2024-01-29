"""Run instrumentation for all benchmarks

This script runs Merlin's instrumentation for all Jotai benchmarks in a given
directory using the 'run.sh' script. The output for the instrumentation is saved
in the 'output/' directory.

The script reports any errors that occur during the execution of the
instrumentation.

Usage:
    python runInstrumentation.py <directory>

Arguments:
    directory (str): Path to the directory with the programs to be instrumented.
"""

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

    errors = []
    nonNewton = 0
    for input in inputs:
        print(f'Running: {input}')
        func_target = find_func_name(input)
        proc = run(f'./scripts/run.sh {dir_name}/{input} {input} {func_target} --count-non-newton',
                   shell=True, capture_output=True, text=True)

        if proc.returncode != 0:
            errors.append((input, proc.stderr))

        lines = [x.strip() for x in proc.stdout.split('\n')]
        nonNewton += int(lines[1].split(': ')[1])

    print(f'\n\nNon-Newton counters: {nonNewton}\n\n')
    if len(errors) > 0:
        print('\n\n======================ERRORS======================\n\n')
        for (input, err) in errors:
            print(f'======================{input}======================')
            print(err)
