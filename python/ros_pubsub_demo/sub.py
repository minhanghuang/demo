#!/usr/bin/python3
# -*- coding:UTF-8 -*-


import rospy
from std_msgs.msg import UInt32MultiArray


class Subscriber(object):

    def __init__(self):
        rospy.Subscriber(  # 对位，不对位没有数据
            "/hadmap_server/planning_path",  # topic
            UInt32MultiArray,  # msgs
            self.callback,
            queue_size=1,
        )

    def callback(self, data):
        print("data:",data)
        return None

    def run(self):
        rospy.spin()
        return None


if __name__ == '__main__':
    print("sub")
    rospy.init_node('test_sub', disable_signals=True)
    sun = Subscriber()
    sun.run()
