# Method Decorator


class GMAT:

    score = 100


    # Question Type: Critical Thinking
    @classmethod
    def class_foo(cls):
        print('class method')

    @staticmethod
    def static_foo():
        print('static method')


GMAT.class_foo()

GMAT.static_foo()
g = GMAT()
g.static_foo()
g.class_foo()


print('\n')







