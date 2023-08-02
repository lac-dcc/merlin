from os import listdir
from subprocess import run

if __name__ == '__main__':
    inputs = listdir('../experiments/sample_2_final')
    for input in inputs:
        print(f'Running: {input}')
        proc = run(
            f'./bin/main < ../experiments/sample_2_final/{input} > output/{input}', shell=True)