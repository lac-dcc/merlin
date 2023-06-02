from os import listdir, remove
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

    sub.run('mkdir -p programs', shell=True)
    sample_size = int(argv[1])
    inputs = listdir('./output')
    for input in sample(inputs, sample_size):
        sub.run('clang output/' + input + ' -std=c99 -o programs/' + input[:-2], shell=True) 

    sub.run('mkdir -p prog_out', shell=True)
    for input in listdir('programs'):
        sub.run('./programs/'+input + ' 0 > prog_out/'+input+'0.txt', shell=True)
        sub.run('./programs/'+input + ' 1 > prog_out/'+input+'1.txt', shell=True)
        sub.run('./programs/'+input + ' 2 > prog_out/'+input+'2.txt', shell=True)
        sub.run('./programs/'+input + ' 3 > prog_out/'+input+'3.txt', shell=True)
        sub.run('./programs/'+input + ' 4 > prog_out/'+input+'4.txt', shell=True)
        sub.run('./programs/'+input + ' 5 > prog_out/'+input+'5.txt', shell=True)

    for input in listdir('prog_out'):
        input_file = open('prog_out/' + input, 'r', encoding='unicode_escape')
        line = input_file.readline().strip()
        if line == 'Usage:':
            remove('prog_out/' + input)
        input_file.close()