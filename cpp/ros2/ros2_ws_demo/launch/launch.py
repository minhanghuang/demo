import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription(
            [
                launch_ros.actions.Node(
                    package='pub1_demo', 
                    node_executable='pub1',
                    output='screen'
                ),
                launch_ros.actions.Node(
                    package='pub2_demo', 
                    node_executable='pub2',
                    output='screen'
                )
            ],
        )
