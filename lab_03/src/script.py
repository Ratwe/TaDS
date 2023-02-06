for size in [50, 100, 500]:
    for percent in range(0, 101):

        filename = f'../data/data{size}_{percent}.txt'

        f = open(filename, 'w')

        f.write('1\n')
        f.write(str(size) + '\n')
        f.write(str(size) + '\n')
        f.write(str(int(size * size * percent / 100)) + '\n')
        f.write(str(size) + '\n')
        f.write(str(size) + '\n')
        f.write(str(int(size * size * percent / 100)) + '\n')

        f.close()
