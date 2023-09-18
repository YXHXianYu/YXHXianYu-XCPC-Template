import math

def work():
    print(math.atan2(0, 2))
    print(math.atan2(1, 2))
    print(math.atan2(2, 2))
    print(math.atan2(2, 1))
    print(math.atan2(2, 0))
    print(math.atan2(2, -1))
    print(math.atan2(2, -2))
    print(math.atan2(1, -2))
    print(math.atan2(0, -2))
    print(math.atan2(-1, -2))
    print(math.atan2(-2, -2))
    print(math.atan2(-2, -1))
    print(math.atan2(-2, 0))
    print(math.atan2(-2, 1))
    print(math.atan2(-2, 2))
    print(math.atan2(-1, 2))
    print(math.atan2(0, 2))
    

def main():
    t = 1
    # t = int(input())
    while t > 0:
        work()
        t -= 1

main()