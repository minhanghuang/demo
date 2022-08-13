import os
import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription(
            [
                launch_ros.actions.Node(
                    package='pcl_demo',
                    executable='pcl_demo',
                    output='screen'
                ),
            ],
        )

