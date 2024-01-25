import rospy
from std_srvs.srv import Trigger, TriggerResponse
from std_srvs.srv import SetBool, SetBoolResponse


def set_bool_callback(request):
    print("request: {}".format(request))
    response = SetBoolResponse()
    response.success = True
    response.message = "Hey, roger that; we'll be right there!"
    return response


def common_service_callback1(req, service_name):
    print("Received request from {}".format(service_name))

    response = None
    if "/demo/service/2" == service_name:
        print("SetBool request")
        response = SetBoolResponse()
        response.success = True
        response.message = "setbool response"

    elif "/demo/service/3" == service_name:
        print("Trigger request")
        response = TriggerResponse()
        response.success = True
        response.message = "trigger response"

    return response


def common_service_callback2(req, service_name, response):
    print("Received request from {}".format(service_name))
    return response


if __name__ == "__main__":
    # /opt/ros/noetic/share/std_srvs/srv/SetBool.srv
    print("ros service running ...")
    rospy.init_node('demo_service_node')
    service1 = rospy.Service("/demo/service/1", SetBool, set_bool_callback)
    service2 = rospy.Service(
        "/demo/service/2",
        SetBool,
        lambda req: common_service_callback1(
            req,
            "/demo/service/2"
        ))
    service3 = rospy.Service(
        "/demo/service/3",
        Trigger,
        lambda req: common_service_callback2(
            req,
            "/demo/service/3",
            TriggerResponse(True, "trigger response"),
        )
    )
    try:
        service3 = rospy.Service(
            "/demo/service/3",
            Trigger,
            lambda req: common_service_callback2(
                req,
                "/demo/service/3",
                TriggerResponse(True, "trigger response"),
            )
        )
    except Exception as e:
        pass

    rospy.spin()
