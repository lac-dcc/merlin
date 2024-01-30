"""Count non-newtons counters for a given directory

This script instruments programs in a specified directory, utilizing the --count-non-newton flag.
It counts the occurrences of non-Newton counters found within the programs from the directory.

Usage:
    python countNonNewton.py <directory>

Arguments:
    directory (str): Path to the directory with the programs to count non-newton counters.
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
