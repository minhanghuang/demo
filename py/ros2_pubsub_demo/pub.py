from time import sleep
import rclpy
from std_msgs.msg import String


if __name__ == "__main__":
    print("ros py pub")
    rclpy.init()

    node = rclpy.create_node("py_pub")

    publisher = node.create_publisher(String, 'topic', 10)

    msg = String()

    i = 0
    while rclpy.ok():
        msg.data = 'Hello World: %d' % i
        print("pub:",msg)
        i += 1
        publisher.publish(msg)
        sleep(0.5)  # seconds

    node.destroy_node()
    rclpy.shutdown()
