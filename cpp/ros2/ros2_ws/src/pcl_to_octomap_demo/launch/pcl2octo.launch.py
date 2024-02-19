import os
import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription(
            [
                launch_ros.actions.Node(
                    package='pcl_to_octomap_demo',
                    executable='pcl_to_octomap_demo',
                    output='screen'
                ),
                launch_ros.actions.Node(
                    package='octomap_server',
                    executable='octomap_server_node',
                    output='screen',
                    parameters=[{
                        'resolution': 0.1,
                        'frame_id': "map",
                    }],
                    remappings=[('/cloud_in', '/pcl2octo')],
                ),

            ],
        )

