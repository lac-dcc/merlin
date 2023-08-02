from os import listdir, popen
from sys import argv, stderr
from subprocess import run

if __name__ == '__main__':
    if len(argv) < 2:
        print(f'Usage: {argv[0]} <sample_dir>', file=stderr)
        exit(1)

    sample_dir = argv[1]
    programs_dir = f'{sample_dir}_programs'
    run(f'mkdir -p {programs_dir}', shell=True)
    run(f'rm -f {programs_dir}/*', shell=True)
    for input in listdir(sample_dir):
        run(
            f'clang {sample_dir}/{input} -std=c99 -o {programs_dir}/{input[:-2]}', shell=True)

    output_dir = f'{sample_dir}_out'
    run(f'mkdir -p {output_dir}', shell=True)
    run(f'rm -f {output_dir}/*', shell=True)

    for input in listdir(programs_dir):
        output_str = ''
        for entry in range(5):
            out = run(f'{programs_dir}/{input} {entry}', shell=True, capture_output=True, text=True).stdout
            if out.split('\n')[0].strip() != 'Usage:':
                output_str += out + '\nend\n'

        with open(f'{output_dir}/{input}.txt', 'w') as output:
            output.write(output_str)

for( i : points) {
    cin >> pa >> pb;
    pointsA.append(pa); pointsB.append(pb);
}