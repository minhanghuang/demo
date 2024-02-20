# 使用

1. 编译

```shell
colcon build
```

2. 运行

```shell
source install/setup.zsh
```

*两种方式：*

- 启动节点

```shell
ros2 run lifecycle_demo lifecycle_demo_node
```

- 启动launch文件

```shell
ros2 launch lifecycle_demo lifecycle_demo_launch.py
```

3. 更新节点状态

```shell
# 初始化publisher和timer
ros2 lifecycle set /lifecycle_demo_node configure

# 激活publisher和定时器，从而使能发布
ros2 lifecycle set /lifecycle_demo_node activate
```

```shell
# 停止publisher和timer
ros2 lifecycle set /lifecycle_demo_node deactivate

# 销毁publisher和timer
ros2 lifecycle set /lifecycle_demo_node cleanup
```

# 更多

- 控制

查看当前的生命周期节点: `ros2 lifecycle nodes`

查看某个生命周期节点所处的状态: `ros2 lifecycle get <lifecycle_node>`

列出某个生命周期节点仍可切换的状态: `ros2 lifecycle list <lifecycle_node>`

切换某个生命周期节点的状态: `ros2 lifecycle set <lifecycle_node> configure/activate/cleanup/deactivate/shutdown`

