class Cat:
    def __init__(self):
        pass

    def calc_time(self, func):
        def wrapper(*args, **kwargs):
            print("before")
            result = func(*args, **kwargs)
            print("after\n")
            return result
        return wrapper

    @property
    def run1(self):
        return self.calc_time(self._run1)

    def _run1(self):
        print("cat run1")

    @property
    def run2(self):
        return self.calc_time(self._run2)

    def _run2(self, msg):
        print("cat run2 {}".format(msg))


class Dog:
    def __init__(self):
        pass
        self.name = "001"

    @staticmethod
    def calc_distance(func):
        def wrapper(*args, **kwargs):
            print("before")
            result = func(*args, **kwargs)
            print("after\n")
            return result
        return wrapper

    @staticmethod
    def calc_time(func):
        def wrapper(instance, *args, **kwargs):
            print("before")
            print("name: {}".format(instance.name))
            result = func(instance, *args, **kwargs)
            print("after\n")
            return result
        return wrapper

    @staticmethod
    def calc_energy(param):
        def decorator(func):
            def wrapper(self, arg):
                # 在调用成员函数之前的处理，可以访问类的成员变量
                print(f"Decorator parameter: {param}")
                print(f"Class variable: {self.name}")
                result = func(self, arg)
                # 在调用成员函数之后的处理
                print("Decorator completed")
                return result
            return wrapper
        return decorator

    @calc_distance
    def run1(self):
        print("dog run1")

    @calc_time
    def run2(self):
        print("dog run2")

    @calc_energy(5)
    def run3(self, msg):
        print("dog run3 {}".format(msg))


if __name__ == "__main__":
    cat = Cat()
    cat.run1()
    cat.run2("传1个参数")

    dog = Dog()
    dog.run1()
    dog.run2()
    dog.run3("传1个参数")
