#!/usr/bin/python3
# -*- coding:UTF-8 -*-


import rospy
from std_msgs.msg import String


class Subscriber(object):
    def __init__(self):
        rospy.Subscriber(
            "/chatter",
            String,
            self.chatter_callback,
            queue_size=1,
        )
        rospy.Subscriber(
            "/chatter2",
            String,
            self.chatter2_callback,
            queue_size=1,
        )
        rospy.Subscriber(
            "/chatter3",
            String,
            lambda msg: print(f"Received message: {msg.data}"),
            queue_size=1,
        )

    # 装饰器函数
    def timing_decorator(param):
        def decorator(callback):
            def wrapper(self, msg):
                print("param: {}".format(param))
                print("before")
                result = callback(self, msg)
                print("after")
                return result
            return wrapper
        return decorator

    @timing_decorator(1)
    def chatter_callback(self, msg):
        print("msg:", msg)
        return None

    def chatter2_callback(self, msg):
        print("msg:", msg)
        return None

    def run(self):
        rospy.spin()
        return None


if __name__ == '__main__':
    rospy.init_node('test_sub_node', disable_signals=True)
    sub = Subscriber()
    sub.run()
