#!/usr/bin/env python
import sys
import unittest
import rostest
import rospy


class TestDemo(unittest.TestCase):

    def test_1(self):
        self.assertTrue(True)
        # self.assertTrue(False)


if __name__ == '__main__':
    rospy.init_node("demo_test_node")
    rostest.run(
        package="unittest_demo",
        test_name="demo_test",
        test=TestDemo,
        sysargs=sys.argv,
    )
