from os import listdir
from subprocess import run

if __name__ == '__main__':
    run('rm -rf output', shell=True)
    inputs = listdir('../test/jotai_benchmarks')
    print(len(inputs))
    errors = []
    for input in inputs:
        print(f'Running: {input}')
        proc = run(f'./run.sh ../test/jotai_benchmarks/{input} {input}', shell=True, capture_output=True, text=True)
        if proc.returncode != 0:
            errors.append((input, proc.stderr))

    print('\n\n======================ERRORS======================\n\n')
    for (input, err) in errors:
        print(f'======================{input}======================')
        print(err)
