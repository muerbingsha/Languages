# Magic Methods
# Reference:
# https://rszalski.github.io/magicmethods/
# https://www.python-course.eu/python3_magic_methods.php



class Penguin():
    public_variable = 'public_variable'
    _protected_variable = 'protected_variable'
    __private_variable = 'private_variable'
    info = {}
    height = 1.0
    name = 'penguine'

    ## 1
    # creat new instance
    def __new__(cls, *args, **kwargs):
        print('__new__')
        instance = object.__new__(cls, *args, **kwargs)
        return instance

    # initialize new instance
    def __init__(self):
        print('constructor __init__')


    def __del__(self):
        print('destructor __del__')


    ## 2
    # bird = Penguin()
    # print(bird)
    def __str__(self):
        return '__str__ '

    # bird
    def __repr__(self):
        return '__repr__ '


    ## 3
    def __getitem__(self, item):
        return self.info[item]

    def __setitem__(self, key, value):
        self.info[key] = value

    ## 4
    # compare
    def __cmp__(self, other):
        pass

    # =
    def __eq__(self, other):
        pass

    # !=
    def __ne__(self, other):
        pass

    # <
    def __lt__(self, other):
        pass

    # >
    def __gt__(self, other):
        pass

    # <=
    def __le__(self, other):
        pass

    # >=
    def __ge__(self, other):
        pass


    # operator
    # +
    def __add__(self, other):
        print('__add__')

    # -
    def __sub__(self, other):
        print('__sub__')

    # *
    def __mul__(self, other):
        pass

    # //
    def __floordiv__(self, other):
        print('__floordiv__')

    # /
    def __truediv__(self, other):
        print('__truediv__')

    # %
    def __mod__(self, other):
        print('__mod__')

    # **
    def __pow__(self, power, modulo=None):
        print('__pow__')

    # <<
    def __lshift__(self, other):
        print('__lshift__')

    # >>
    def __rshift__(self, other):
        print('__rshift__')

    # logic and &
    def __and__(self, other):
        print('__and__')

    # logc xor ^
    def __xor__(self, other):
        print('__xor__')

    # logic or |
    def __or__(self, other):
        print('__or__')


    def __len__(self):
        print('__len__')


if __name__ =='__main__':
    print('\n')
    bird = Penguin()# __new__ + __init__


    print('\n')
    print(bird)     # __str__
    bird            # __repr__


    print('\n')
    # __setitem__
    bird['food'] = 'fish'
    bird['enemy'] = 'seal'
    # __getitem__
    print(bird['food'])
    print(bird['enemy'])


    print('\n')
    bird + 'John'   # __add__
    bird - 'John'
    bird * 'John'
    bird // 'John'
    bird / 'John'
    bird % 'John'
    bird ** 'John'
    bird << 'John'
    bird >> 'John'
    bird & 'John'
    bird ^ 'John'
    bird | 'John'



    del bird        # __del__


