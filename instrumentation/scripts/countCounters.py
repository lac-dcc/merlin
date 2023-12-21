"""Run instrumented programs and count the number of counters

This scripts compiles and runs programs from a directory that contains
instrumented Jotai programs and counts the number of counters that were inserted
by Merlin.

Usage:
    python countCounters.py <sample_dir>

Arguments:
    input_dir (str): Path to the directory where programs are.

"""

from os import listdir
from sys import argv, stderr
from subprocess import run

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <input_dir>', file=stderr)
        exit(1)

    input_dir = argv[1]
    programs_dir = f'exp_bin/'
    run(f'mkdir -p {programs_dir}', shell=True)
    run(f'rm -f {programs_dir}/*', shell=True)
    for input in listdir(input_dir):
        if input.endswith('.txt'):
            continue

        print(f'Compiling: {input}')
        run(
            f'clang {input_dir}/{input} -std=c99 -o {programs_dir}/{input[:-2]}', shell=True, capture_output=True)

    counters = 0
    programs = listdir(programs_dir)
    for program in programs:
        print(f'Running: {program}')
        out = run(f'{programs_dir}/{program} 0',
                    shell=True, capture_output=True, text=True, encoding='unicode_escape').stdout
        lines = out.split('\n')
        if lines[0].strip() == 'Usage:':
            continue

        counters += int(lines[0].split(': ')[1])
    
    print(f'NUMBER OF PROGRAMS: {len(programs)}')
    print(f'NUMBER OF COUNTERS: {counters}')