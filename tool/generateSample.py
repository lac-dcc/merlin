from os import listdir
from random import sample, randrange, seed
from sys import argv, stderr, maxsize
from subprocess import run

if __name__ == '__main__':
    if len(argv) < 3:
        print(f'Usage: {argv[0]} <sample_size> <output> [seed]', file=stderr)
        exit(1)

    if len(argv) == 4:
        rand_seed = int(argv[3])
    else:
        rand_seed = randrange(maxsize)
    seed(rand_seed)
    print(rand_seed)

    sample_output = argv[2]
    run(f'mkdir -p {sample_output}', shell=True)
    run(f'rm -f {sample_output}/*', shell=True)
    programs = listdir('./output')
    sample_size = int(argv[1])
    for input in sample(programs, sample_size):
        run(f'cp ./output/{input} {sample_output}/{input}', shell=True)

    run(f'touch {sample_output}/seed.txt && echo "{rand_seed}" > {sample_output}/seed.txt', shell=True)
