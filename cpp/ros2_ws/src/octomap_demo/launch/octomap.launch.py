import os
from ament_index_python.packages import get_package_share_directory
import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    config = os.path.join(get_package_share_directory('octomap_demo'), 'param', 'octomap.yaml') 
    return launch.LaunchDescription(
            [
                launch_ros.actions.Node(
                    package='octomap_demo',
                    executable='octomap_demo',
                    output='screen',
                    parameters = [config],
                ),
            ],
        )

