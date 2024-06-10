import math
import functools

PI = math.acos(-1.0)
PId2 = PI / 2.0
PId2m3 = PI / 2.0 * 3.0
PIm2 = PI * 2.0
eps = 1e-10

radius = 0.0
n = 0.0
a = []
land = []

def getTime(i: int) -> float:
    t1 = (math.sqrt(a[i][0] * a[i][0] + a[i][1] * a[i][1]) - radius) / a[i][2]
    land[i] = t1 # get land here
    t2 = radius * PI / a[i][3]
    return t1 + t2

def getAngle(i: int) -> float:
    if a[i][0] == 0:
        if a[i][1] > 0:
            return PId2
        else:
            return -PId2
    elif a[i][1] == 0:
        if a[i][0] > 0:
            return 0
        else:
            return PI
    else:
        return math.atan2(a[i][1], a[i][0])
        

def check(x: float) -> bool:
    b = [(0, 0)]
    for i in range(1, n + 1):
        if x > land[i]:
            b.append((i, a[i][3] * (x - land[i])))
    if len(b) == 1:
        return False
    if len(b) == 2:
        return b[1][1] >= radius * PI
    b.append(b[1])

    m = len(b) - 1
    c = [(0, 0), b[1]]
    cnt = 1
    for i in range(2, m + 1):
        if a[c[cnt][0]][4] == a[b[i][0]][4]:
            if c[cnt][1] < b[i][1]:
                c[cnt] = b[i]
        else:
            cnt += 1
            c.append(b[i])
    
    for i in range(2, cnt + 1):
        delta_angle = a[c[i][0]][4] - a[c[i-1][0]][4]
        if delta_angle < 0.0:
            delta_angle += PIm2
        
        delta_dis = delta_angle * radius
        genuine_dis = c[i][1] + c[i-1][1]

        if genuine_dis < delta_dis:
            return False
    
    return True


def work():
    global radius
    global n
    global a
    global land

    t = [int(i) for i in input().split()]
    radius = t[0]
    n = t[1]
    
    a = [[] for i in range(n + 1)]
    land = [0] * (n + 1)

    for i in range(1, n + 1):
        a[i] = [int(i) for i in input().split()]
    
    for i in range(1, n + 1):
        # print(i, flush=True)
        a[i].append(getAngle(i))

    def compare(A, B):
        if A[4] < B[4]:
            return -1
        elif A[4] > B[4]:
            return 1
        else:
            return 0
    a = [0] + sorted(a[1:], key=functools.cmp_to_key(compare))

    # print(a)
    
    R = getTime(1)
    for i in range(2, n + 1):
        R = min(R, getTime(i))
    
    if n == 1:
        print(R)
        return None

    # print(R)

    L = R / n
    ans = R
    while R - L > eps:
        mid = (L + R) / 2
        if check(mid):
            ans = mid
            R = mid
        else:
            L = mid

    print(ans)


def main():
    t = 1
    t = int(input())
    while t > 0:
        work()
        t -= 1

main()