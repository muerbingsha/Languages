
a = list(filter(lambda x: True if x%3 == 0 else False, range(100)))
print(a)


def make_repeat(n):
    return lambda s: s*n

d = make_repeat(2)
print(d(8))