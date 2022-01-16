import zmq
import time
from protos.hdmap_pb2 import Position


class Publisher(object):

    def __init__(self, topic):
        self.topic = topic
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.PUB)
        self.socket.bind("ipc:///var/log/trunk/haha.ipc")
        self.position = Position()
        self.position.point.x = 1
        self.serialize_data = self.position.SerializeToString()

    def run(self):
        topic = bytes(self.topic,encoding = "utf8")
        while True:
            print(self.position)
            self.socket.send_multipart([topic, self.serialize_data])
            time.sleep(1)


if __name__ == '__main__':
    print("pub topic")
    pub = Publisher("/haha/hdmap")
    pub.run()