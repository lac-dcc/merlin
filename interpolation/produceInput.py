from subprocess import run
from sys import argv, stderr
from os import listdir

if __name__ == '__main__':
    if len(argv) < 3:
        print(f'Usage: {argv[0]} <input_file> <output_name>', file=stderr)
        exit(1)
    
    input_file = argv[1]
    output_name = argv[2]
    run(f'mkdir -p ./input/', shell=True)
    with open(input_file, 'r') as file:
        interp_in = ''
        num_counters = -1
        instrumentation_data = file.read().split('\nend\n')[:-1]
        for data in instrumentation_data:
            lines = data.split('\n')

            if num_counters == -1:
                num_counters = int(lines[0].split(': ')[1])
                interp_in += str(num_counters) + '\n'
                interp_in += str(len(instrumentation_data)) + '\n'
                interp_in += '\n'.join(lines[1:(2*num_counters + 1)]) + '\n'

            interp_in += '\n'.join(lines[(2*num_counters + 1):])

        entry_file = open(f'input/{output_name}', 'w')
        entry_file.write(interp_in)
        entry_file.close()