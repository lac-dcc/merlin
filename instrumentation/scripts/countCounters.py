"""Run instrumented programs and count the number of counters

This scripts compiles and runs programs from the 'output' directory and counts 
the number of counters that were inserted during instrumentation.

The script assumes that the 'output' directory contains all instrumented
programs from the Jotai benchmark suite. The compilation is done using clang and
the binaries are saved in a separate directory.

All Jotai benchmarks can receive arguments from 0 to 5. The script tries all the
possible arguments and saves the outputs in a separate text file. These outputs
can be used by Merlin's interpolation.

Usage:
    python countCounters.py

"""

from os import listdir
from subprocess import run

if __name__ == '__main__':
    input_dir = '../experiments/sample'
    programs_dir = f'exp_bin/'
    run(f'mkdir -p {programs_dir}', shell=True)
    run(f'rm -f {programs_dir}/*', shell=True)
    for input in listdir(input_dir):
        print(f'Compiling: {input}')
        run(
            f'clang {input_dir}/{input} -std=c99 -o {programs_dir}/{input[:-2]}', shell=True, capture_output=True)

    counters = 0
    programs = listdir(programs_dir)
    for program in programs:
        print(f'Running: {program}')
        for entry in range(5):
            out = run(f'{programs_dir}/{program} {entry}',
                      shell=True, capture_output=True, text=True, encoding='unicode_escape').stdout

            lines = out.split('\n')
            if lines[0].strip() == 'Usage:':
                break

            counters += int(lines[0])
    
    print(f'NUMBER OF PROGRAMS: {len(programs)}')
    print(f'NUMBER OF COUNTERS: {counters}')