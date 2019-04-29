# How decorator works
# Reference:
# https://realpython.com/primer-on-python-decorators/#functions
# step 1: inner function
def parent_a():
    print('Parent function a')

    def child_first_a():
        print('first child a')

    def child_second_a():
        print('second child a')

    child_first_a()
    child_second_a()



# step 2: inner function (return)
def parent_b(num):
    print('Parent function b')


    def child_first_b():
        return 'first child b'

    def child_second_b():
        return 'second child b'

    # selective inner functions
    if num == 1:
        return child_first_b()  # function execution
    elif num == 2:
        return child_second_b   # function reference
    else:
        print('wrong')



print('\n-----inner functions----\n')
parent_a()
r1 = parent_b(1)
print(r1) # str
r2 = parent_b(2)
print(r2()) # func



# step 3: decorator
# function as paramter
def hello(fn):
    def wrapper():
        print('wrapper before fn')
        fn()
        print('wrapper end fn')
    return wrapper


def foo():
    print('foo')


@hello
def whee():
    print('whee')


print('\n-----wrapper----\n')
hello(foo)()
whee() # whee() = hello(whee)()



print('\n-----wrapper with parameters----\n')
# step 4: pass parameters
def do_twice(fn):
    def wrapper(*args, **kwargs):
        fn(*args, **kwargs)
        fn(*args, **kwargs)
    return wrapper

@do_twice
def greet(name, age):
    print(f'hello {name}, {age}')


greet('Mary', 30)