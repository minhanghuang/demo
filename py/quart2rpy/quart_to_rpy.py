import sys
from math import cos, sin, pi, atan2, asin

if __name__ == '__main__':
    print("四元素转欧拉角")
    quaternion = {
        "x": 0.0056370173099,
        "y": -0.00269722484417,
        "z": 0.477472473219,
        "w": 0.878624485393,
    }
    euler = {
        "roll": 0,
        "pitch": 0,
        "yaw": 0,
    }
    x = quaternion["x"]
    y = quaternion["y"]
    z = quaternion["z"]
    w = quaternion["w"]

    euler["roll"] = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y))
    euler["pitch"] = asin(2 * (w * y - z * x))
    euler["yaw"] = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y))

    print("四元素: {}".format(quaternion))
    print("欧拉角: {}".format(euler))
