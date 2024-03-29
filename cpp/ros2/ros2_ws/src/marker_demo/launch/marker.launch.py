import os
import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription(
            [
                launch_ros.actions.Node(
                    package='marker_demo',
                    executable='marker_demo',
                    output='screen'
                ),
            ],
        )

