```shell
cd ws/src
catkin create pkg ros_demo roscpp std_msgs
```

```shell
catkin config --install --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
catkin build
```
