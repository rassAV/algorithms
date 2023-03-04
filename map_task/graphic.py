import matplotlib.pyplot as plt
import sys
import time

def paint_gr(name, x, y, xl, yl):
    plt.figure(name)
    plt.title(name)
    plt.plot(x, y)
    plt.xlabel(xl)
    plt.ylabel(yl)

data = input().split()

map_times = list(map(float, data[::2]))
map_sizes = list(map(int, data[1::2]))
n = []
for i in range(len(map_sizes)):
    n.append(10**i)

dict_times = []
dict_sizes = []
for i in n:
    t1 = time.perf_counter()
    d = {x: x for x in range(i)}
    dict_times.append((time.perf_counter() - t1) * 1000) # ms
    dict_sizes.append(sys.getsizeof(d))

paint_gr("MAP зависимость времени в мс от количества элементов", n, map_times, "elements", "ms")
paint_gr("MAP зависимость объёма памяти в байтах от количества элементов", n, map_sizes, "elements", "bytes")

paint_gr("DICT зависимость времени в мс от количества элементов", n, dict_times, "elements", "ms")
paint_gr("DICT зависимость объёма памяти в байтах от количества элементов", n, dict_sizes, "elements", "bytes")

plt.show()