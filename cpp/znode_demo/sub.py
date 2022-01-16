import zmq
from protos.hdmap_pb2 import Position


class Subscriber(object):

    def __init__(self, topic):
        self.topic = topic
        self.data = None
        self.position = Position()
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.SUB)
        self.socket.connect("ipc:///var/log/trunk/haha.ipc")
        self.socket.setsockopt_string(zmq.SUBSCRIBE, "")

    def run(self):
        while True:
            topic, self.data = self.socket.recv_multipart()
            self.position.ParseFromString(self.data)
            print("topic:{} data:{}".format(topic, self.position))


if __name__ == '__main__':
    print("sub topic")
    sub = Subscriber("/haha/hdmap")
    sub.run()
