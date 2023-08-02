from os import listdir, remove
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
        run(
            f'clang {sample_dir}/{input} -std=c99 -o {programs_dir}/{input[:-2]}', shell=True)

    output_dir = f'{sample_dir}_out'
    run(f'mkdir -p {output_dir}', shell=True)
    run(f'rm -f {output_dir}/*', shell=True)
    for input in listdir(programs_dir):
        run(f'{programs_dir}/{input} 0 > {output_dir}/{input}0.txt', shell=True)
        run(f'{programs_dir}/{input} 1 > {output_dir}/{input}1.txt', shell=True)
        run(f'{programs_dir}/{input} 2 > {output_dir}/{input}2.txt', shell=True)
        run(f'{programs_dir}/{input} 3 > {output_dir}/{input}3.txt', shell=True)
        run(f'{programs_dir}/{input} 4 > {output_dir}/{input}4.txt', shell=True)
        run(f'{programs_dir}/{input} 5 > {output_dir}/{input}5.txt', shell=True)

    for input in listdir(output_dir):
        with open(f'{output_dir}/{input}', 'r', encoding='unicode_escape') as input_file:
            line = input_file.readline().strip()
            if line == 'Usage:':
                remove(f'{output_dir}/{input}')
