# from proto.hello_pb2 import Message
from proto import *

class CreatInstance(object):
    def __init__(self):
        pass

    def instance1(self, name: str, *args, **kwargs):

        (module_name, class_name) = name.rsplit('.', 1)
        module_meta = __import__(module_name, globals(), locals(), [class_name])
        class_meta = getattr(module_meta, class_name)
        return class_meta(*args, **kwargs)




if __name__ == '__main__':

    creat = CreatInstance()
    obj = creat.instance1("proto.hello_pb2.Message")
    obj.name = "haha"
    obj.age = 19
    print(obj)
    print("---")
