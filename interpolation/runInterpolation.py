from subprocess import run
from sys import argv, stderr
from os import listdir

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <input_dir>', file=stderr)
        exit(1)
    
    input_dir = argv[1]
    run(f'mkdir -p ./output/{input_dir}', shell=True)
    # for input in listdir(input_dir):
    #     print(f'Running Interpolation for {input}')
    #     run(f'./bin/interpolator < {input_dir}/{input} > output/{input_dir}/{input}', shell=True)

