from os import listdir
from subprocess import run

if __name__ == '__main__':
    run('rm -rf output', shell=True)
    inputs = listdir('../test/jotai_benchmarks')
    print(len(inputs))
    for input in inputs:
        print(f'Running: {input}')
        run(f'./run.sh ../test/jotai_benchmarks/{input} {input}', shell=True)
