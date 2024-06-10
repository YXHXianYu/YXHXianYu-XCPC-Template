
maxn = int(2e3 + 10)

n = 0
m = 0
cnt = 0

q = [0] * maxn

def turn2char(x: int) -> str:
    if x == 0:
        return ")"
    else:
        return "("

def check() -> bool:
    t = 0
    for i in range(1, n + 1):
        if q[i] == 1:
            t += 1
        else:
            t -= 1
            if t < 0:
                return False
    return t == 0

def dfs(k: int) -> None:
    global cnt
    global q

    if k > n:
        if check() == False:
            return None
        cnt += 1
        if cnt == m:
            for i in range(1, n + 1):
                print(turn2char(q[i]), end="")
            print()
        return None
    
    q[k] = 1
    dfs(k + 1)
    if cnt >= m:
        return None
    q[k] = 0
    dfs(k + 1)

def work():
    global n
    global m
    global cnt
    global q
    
    t = [int(i) for i in input().split()]
    n, m = t[0], t[1]

    dfs(1)


def main():
    t = 1
    # t = int(input())
    while t > 0:
        work()
        t -= 1

main()