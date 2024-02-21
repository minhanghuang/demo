from launch import LaunchDescription
from launch_ros.actions import LifecycleNode


def generate_launch_description():
    return LaunchDescription([
        LifecycleNode(
            package='marker_demo',
            executable='marker_demo_node',
            name='marker_demo_node',  # 节点名
            namespace='',
            output='screen'
        ),
    ])
