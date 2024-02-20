from launch import LaunchDescription
from launch_ros.actions import LifecycleNode


def generate_launch_description():
    return LaunchDescription([
        LifecycleNode(
            package='lifecycle_demo',
            executable='lifecycle_demo_node',
            name='lifecycle_demo_node',  # 节点名
            namespace='',
            output='screen'
        ),
    ])
