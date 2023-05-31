from os import listdir
import subprocess as sub
import os as os

if __name__ == '__main__':
    sub.run('mkdir programs', shell=True)
    for input in listdir('output'):
        sub.run('clang output/' + input + ' -std=c99 -o programs/' + input[:-2], shell=True) 
    sub.run('mkdir prog_out', shell=True)
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
            os.remove('prog_out/' + input)
        input_file.close()