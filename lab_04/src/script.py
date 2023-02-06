from random import randrange

f = open('../data/data1000.txt', 'w')

for i in range(0, 1000):
    f.write(chr(randrange(300, 500)))

f.close()
