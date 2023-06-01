from os import listdir
from random import sample, randrange, seed
from sys import argv, stderr, maxsize
import subprocess as sub

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <num_inputs> [seed]', file=stderr)
        exit(1)

    if len(argv) == 3:
        seed(int(argv[2]))
    else:
        rand_seed = randrange(maxsize)
        seed(rand_seed)
        print(rand_seed)
  
    sub.run('rm -rf output', shell=True)
    inputs = listdir('../test/jotai_benchmarks')
    sample_size = int(argv[1])
    for input in sample(inputs, sample_size):
        print('Running: ' + input)
        sub.run('./run.sh ../test/jotai_benchmarks/' + input + ' ' + input, shell=True) 