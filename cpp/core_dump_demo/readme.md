
- 修改配置 

> 设置core文件的大小

```shell
// 当前终端生效
ulimit -c unlimited
```

> core文件放到当前路径

```shell
// 在docker环境下设置失败 
sudo sysctl -w kernel.core_pattern="core-%e"
```

- 编译

```shell
cmake -DCMAKE_BUILD_TYPE=DEBU ..
make 
```

- 运行/查看


```shell
./core_dump_runner
```

```shell
gbd core_dump_runner core-core_dump_runner
```

```
Core was generated by `./core_dump_runner'.
---Type <return> to continue, or q <return> to quit---
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x000055fc60335906 in main (argc=1, argv=0x7ffd86106378)
    at /home/trunk/work/code/github/demo/cpp/core_dump_demo/main.cc:7
7         *(s + 1000) = 'x';
(gdb)
```

