
n = 0
m = 0
a = [[]]

def preCalc(x: str) -> int:
    if x == "T":
        return 0
    elif x == "E":
        return 1
    elif x == "S":
        return 2
    elif x == "W":
        return 3
    elif x == "N":
        return 4
    else:
        assert(False)

def work():
    global n
    global m
    global a

    t = [int(i) for i in input().split()]
    n = t[0]
    m = t[1]
    a = [[] for i in range(n + 1)]
    for i in range(1, n + 1):
        a[i] = [0] + [preCalc(j) for j in input()]
    
    if a[1][1] == 0:
        print(0)
        return None

    curX = 1
    curY = 1
    cnt = 0
    
    f = [[0] * (m + 1) for i in range(n + 1)]

    mx = [0, 0, 1, 0, -1]
    my = [0, 1, 0, -1, 0]

    while f[curX][curY] != 1:
        f[curX][curY] = 1
        v = a[curX][curY]
        curX, curY = curX + mx[v], curY + my[v]
        cnt += 1

        if curX <= 0 or curX > n or curY <= 0 or curY > m:
            print("Out")
            return None
        if a[curX][curY] == 0:
            print(cnt)
            return None
    
    print("Lost")

def main():
    t = 1
    # t = int(input())
    while t > 0:
        work()
        t -= 1

main()