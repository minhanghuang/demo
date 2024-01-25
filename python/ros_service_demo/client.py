import rospy
from rospy.timer import sleep
from std_srvs.srv import Trigger, TriggerRequest
from std_srvs.srv import SetBool, SetBoolRequest

if __name__ == "__main__":
    # /opt/ros/noetic/share/std_srvs/srv/SetBool.srv
    rospy.init_node('demo_client_node')

    rospy.wait_for_service("/demo/service/1")
    client = rospy.ServiceProxy("/demo/service/1", SetBool)
    req = SetBoolRequest()
    req.data = True
    response = client(req)
    print("resopnse1: {}".format(response))

    sleep(1)
    rospy.wait_for_service("/demo/service/2")
    client = rospy.ServiceProxy("/demo/service/2", SetBool)
    req = SetBoolRequest()
    req.data = True
    response = client(req)
    print("resopnse2: {}".format(response))

    sleep(1)
    rospy.wait_for_service("/demo/service/3")
    client = rospy.ServiceProxy("/demo/service/3", Trigger)
    req = TriggerRequest()
    response = client(req)
    print("resopnse3: {}".format(response))
