import rospy


def main():
    rospy.init_node('param_node')

    # 获取参数: run_id为系统级别的参数, 用于标识ROS系统的每个运行实例
    params = rospy.get_param(
        '/run_id', "")
    rospy.loginfo("Parameter value: %s", params)

    # 获取所有参数
    param_names = rospy.get_param_names()
    all_params = {param: rospy.get_param(param) for param in param_names}
    for param, value in all_params.items():
        rospy.loginfo("Parameter %s: %s", param, value)


if __name__ == "__main__":
    main()
