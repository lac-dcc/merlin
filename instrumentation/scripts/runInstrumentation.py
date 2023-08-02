import pandas as pd
from os import listdir
from subprocess import run

if __name__ == '__main__':
    run('rm -rf output', shell=True)
    inputs = listdir('../test/jotai_benchmarks')
    print(len(inputs))

    results = []
    errors = []
    for input in inputs:
        print(f'Running: {input}')
        proc = run(
            f'./run.sh ../test/jotai_benchmarks/{input} {input}', shell=True, capture_output=True, text=True)

        lines = list(map(lambda x: x.strip(), proc.stdout.split('\n')))
        not_instrumented = len(lines) > 1 and lines[1] == 'Unable to instrument the input'
        results.append({
            'name': input,
            'func_size': int(lines[0]),
            'instrumented': not not_instrumented
        })

        if proc.returncode != 0:

            errors.append((input, proc.stderr))
    if len(errors) > 0:
        print('\n\n======================ERRORS======================\n\n')
        for (input, err) in errors:
            print(f'======================{input}======================')
            print(err)

    columns = ['name', 'func_size', 'instrumented']
    df = pd.DataFrame(data=results, columns=columns)
    df.to_csv('experimentRQ1.csv', mode='w', header=True, index=False)
