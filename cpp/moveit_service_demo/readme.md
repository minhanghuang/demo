
```shell
sudo apt install ros-melodic-moveit
```


```shell
source /opt/ros/melodic/setup.bash
mkdir build && cd build
cmake ..
make -j4 
```

```shell
./server 
./client
```

