from math import cos, sin, pi, atan2, asin


if __name__ == '__main__':
    print("欧拉角转四元素")
    euler = {
        "roll": 0.00733,
        "pitch": -0.0101,
        "yaw": 0.9955,
    }
    quaternion = {
        "x": 0,
        "y": 0,
        "z": 0,
        "w": 0,
    }
    roll = euler.get("roll")
    pitch = euler.get("pitch")
    yaw = euler.get("yaw")
    quaternion['w'] = cos(roll/2)*cos(pitch/2)*cos(yaw/2) + sin(roll/2)*sin(pitch/2)*sin(yaw/2)
    quaternion['x'] = sin(roll/2)*cos(pitch/2)*cos(yaw/2) - cos(roll/2)*sin(pitch/2)*sin(yaw/2)
    quaternion['y'] = cos(roll/2)*sin(pitch/2)*cos(yaw/2) + sin(roll/2)*cos(pitch/2)*sin(yaw/2)
    quaternion['z'] = cos(roll/2)*cos(pitch/2)*sin(yaw/2) - sin(roll/2)*sin(pitch/2)*cos(yaw/2)

    print("欧拉角: {}".format(euler))
    print("四元素: {}".format(quaternion))
