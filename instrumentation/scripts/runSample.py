"""Run programs from a benchmark sample

This scripts compiles and runs programs from a sample of instrumented Jotai
benchmarks. The compilation is done using clang and the binaries are saved in a
separate directory.

All Jotai benchmarks can receive arguments from 0 to 5. The script tries all the
possible arguments and saves the outputs in a separate text file. These outputs
can be used by Merlin's interpolation.

Usage:
    python runSample.py <sample_dir>

Arguments:
    sample_dir (str): Path to the directory where the sample is.
"""

from os import listdir
from sys import argv, stderr
from subprocess import run

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <sample_dir>', file=stderr)
        exit(1)

    sample_dir = argv[1]
    programs_dir = f'{sample_dir}_programs'
    run(f'mkdir -p {programs_dir}', shell=True)
    run(f'rm -f {programs_dir}/*', shell=True)
    for input in listdir(sample_dir):
        if input.endswith('.txt'):
            continue

        run(
            f'clang {sample_dir}/{input} -std=c99 -o {programs_dir}/{input[:-2]}', shell=True)

    output_dir = f'{sample_dir}_out'
    run(f'mkdir -p {output_dir}', shell=True)
    run(f'rm -f {output_dir}/*', shell=True)

    for input in listdir(programs_dir):
        output_str = ''
        for entry in range(5):
            out = run(f'{programs_dir}/{input} {entry}',
                      shell=True, capture_output=True, text=True, encoding='unicode_escape').stdout

            if out.split('\n')[0].strip() == 'Usage:':
                break

            output_str += out

        with open(f'{output_dir}/{input}.txt', 'w') as output:
            output.write(output_str)
