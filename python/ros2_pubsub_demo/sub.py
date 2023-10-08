import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        print("calback:", msg)


if __name__ == "__main__":
    
    print("ros2 py sub")

    rclpy.init()

    node = MinimalSubscriber()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


