from os import listdir
from random import sample, randrange, seed
from sys import argv, stderr, maxsize
import subprocess as sub

if __name__ == '__main__':
    sub.run('rm -rf output', shell=True)
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <num_inputs>', file=stderr)
        exit(1)
    rand_seed = randrange(maxsize)
    seed(rand_seed)
    print(rand_seed)
  
    sample_size = int(argv[1])
    inputs = listdir('../test/jotai_benchmarks')
    for input in sample(inputs, sample_size):
        print('Running: ' + input)
        sub.run('./run.sh ../test/jotai_benchmarks/' + input + ' ' + input, shell=True) 