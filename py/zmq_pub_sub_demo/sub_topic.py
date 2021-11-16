import zmq
from proto.demo_pb2 import Request


class Subscriber(object):

    def __init__(self, topic):
        self.topic = topic
        self.data = None
        self.request = Request()
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.SUB)
        self.socket.connect("ipc://test.ipc")
        self.socket.setsockopt_string(zmq.SUBSCRIBE, "")

    def run(self):
        while True:
            topic, self.data = self.socket.recv_multipart()
            self.request.ParseFromString(self.data)
            print("topic:{} data:{}".format(topic, self.request))


if __name__ == '__main__':
    print("sub topic")
    sub = Subscriber("/hello")
    sub.run()
