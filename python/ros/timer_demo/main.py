#!/usr/bin/env python

import rospy


def timer_callback(event):
    rospy.loginfo("Timer callback triggered at %s", rospy.get_time())


def timer_example():
    rospy.init_node('timer_example', anonymous=True)

    # 10Hz
    rospy.Timer(rospy.Duration(0.1), timer_callback)

    rospy.loginfo("Timer started")

    rospy.spin()


if __name__ == '__main__':
    try:
        timer_example()
    except rospy.ROSInterruptException:
        pass
