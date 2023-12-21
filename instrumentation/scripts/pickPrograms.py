from os import listdir, makedirs
from shutil import copyfile

if __name__ == '__main__':
    sample_dir = '../experiments/sample/'
    new_dir = '../experiments/nonInstrumented/'
    jotai_dir = '../test/jotai_benchmarks/'

    makedirs(new_dir, exist_ok=True)

    for program in listdir(sample_dir):
        copyfile(f'{jotai_dir}{program}', f'{new_dir}{program}')