

def work():
    t = [int(i) for i in input().split()]
    n = t[0]
    k = t[1]

    ans = 1
    a = 2
    while k > 0:
        if (k & 1) > 0:
            ans = ans * a
        a = a * a
        k >>= 1

        if ans >= n:
            print("Your wish is granted!")
            return None
    print("You will become a flying monkey!")

def main():
    t = 1
    # t = int(input())
    while t > 0:
        work()
        t -= 1

main()