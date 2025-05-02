def get_root(p):
    div = []
    cur = p - 1
    i = 2
    while i * i <= cur:
        if cur % i == 0:
            div.append(i)
            while cur % i == 0:
                cur //= i
        i += 1
    if cur > 1:
        div.append(cur)
    primitive_root = 2
    while True:
        found = True
        for d in div:
            if pow(primitive_root, (p - 1) // d, p) == 1:
                found = False
                break
        if found:
            break
        primitive_root += 1
    print(f'primitive root: {primitive_root}')
    pw2 = 0
    cur = p - 1
    while cur % 2 == 0:
        cur //= 2
        pw2 += 1
    ntt_root = pow(primitive_root, cur, p)
    print(f'ntt root: {ntt_root}, of order 2^{pw2}')


get_root(int(input()))