from os import listdir
import subprocess as sub

if __name__ == '__main__':
    sub.run('rm -rf output', shell=True)
    inputs = listdir('../test/jotai_benchmarks')
    print(len(inputs))
    for input in inputs:
        print('Running: ' + input)
        sub.run('./run.sh ../test/jotai_benchmarks/' + input + ' ' + input, shell=True) 