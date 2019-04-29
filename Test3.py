# getter and setter

class Celsius:
    tem = 0

    def __init__(self, temperature = 0):
        self.set_temperature(temperature) # check temperature validity

    def to_fahrenheit(self):
        return (self.tem * 1.8) + 32

    ## traditional getter and setter
    # getter
    def get_temperature(self):
        return self.tem

    # setter (set value check)
    def set_temperature(self, value):
        if value < -273:
            raise ValueError("Temperature below 273 is invalid")
        self.tem = value




men = Celsius()

# don't check
men.tem = -300
print(men.get_temperature())

# men.set_temperature(-300) # check




class Student:
    # getter
    @property
    def score(self):
        return self._score

    # setter
    # @property's fn
    @score.setter
    def score(self, value):
        if value < 0 or value > 100:
            raise ValueError('invalid score')
        self._score = value


print('\n-----@property-----\n')
s = Student()
s.score = 60    # setter
print(s.score)  # getter

s._score = -100
print(s._score)
print(s.score)


