from subprocess import run
from sys import argv, stderr
from os import listdir

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <input_dir>', file=stderr)
        exit(1)
    
    input_dir = argv[1]
    for input in listdir(input_dir):
        with open(f'{input_dir}/{input}', 'r') as file:
            interp_in = ''
            offset = 0
            calls = file.read().split('\nend\n')[:-1]
            print(calls)
            for call in calls:
                for line in call.split('\n')[offset:-1]:
                    interp_in += line + '\n'
                    if offset == 0:
                        offset = int(line) + 1
                        interp_in += str(len(calls)) + '\n'


            print(f'\n{input}')
            print(interp_in)

