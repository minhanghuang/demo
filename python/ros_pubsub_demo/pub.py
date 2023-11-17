#!/usr/bin/python3
# -*- coding:UTF-8 -*-
import rospy
from std_msgs.msg import String


if __name__ == '__main__':

    print("pub")
    rospy.init_node('test_talker_node', anonymous=True)
    pub = rospy.Publisher('/chatter', String, queue_size=1)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        pub.publish(hello_str)
        rate.sleep()
