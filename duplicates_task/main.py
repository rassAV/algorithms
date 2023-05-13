import time
import random
import sys
from pathlib import Path


def find_duplicates(files: list[str], hash_function: callable) -> list[str]:
    hash_file = []
    dublicates = 0
    all_time = 0
    for file in files:
        with open(file, 'rb') as f:
            start_time = time.time()
            hash_ = hash_function(f.read())
            all_time += time.time() - start_time 
            if hash_ in hash_file:
                dublicates += 1
            else:
                hash_file.append(hash_) 
    return dublicates, all_time

    
def hash_crc(line: str):
    h = 0
    for i in line:
        highorder  = h & 0xf8000000
        h = h << 5
        h = h ^ (highorder >> 27)
        h = h ^ i
    return h

def hash_pjw(line: str):
    h = 0
    for i in line:
        h = (h << 4) + i
        g = h & 0xf0000000
        if g != 0:
            h = h ^ (g >> 24)
            h = h ^ g
    return h

def hash_buz(line: str):
    h = 0
    R = dict()
    for i in line:
        highorder = h & 0x80000000
        h = h << 1
        h = h ^ (highorder >> 31)
        if not (i in R):
            R[i] = random.randint(0, sys.maxsize)
        h = h ^ R[i]
    return h

def hash_def(line: str):
    return hash(line)


def main():
    hashs = [hash_crc, hash_pjw, hash_buz, hash_def]
    files = sorted(Path('.').glob('out/*.txt'))
    files = list(map(str, files))
    for i in hashs:
        dublicates, time = find_duplicates(files, i)
        print(i.__name__)
        print("Dublicates: ",dublicates)
        print("Time: ",time)
        print()

main()
