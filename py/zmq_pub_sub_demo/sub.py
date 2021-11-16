import zmq
from proto.demo_pb2 import Request


class Subscriber(object):

    def __init__(self):
        self.data = None
        self.request = Request()
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.SUB)
        self.socket.connect("ipc://test.ipc")
        self.socket.setsockopt_string(zmq.SUBSCRIBE, '')

    def run(self):
        while True:
            self.data = self.socket.recv_multipart()
            self.request.ParseFromString(self.data[0])
            print("recv: ",self.request)


if __name__ == '__main__':
    print("sub")
    sub = Subscriber()
    sub.run()
