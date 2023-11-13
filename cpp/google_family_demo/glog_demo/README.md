1. 安装

```shell
git clone https://gitee.com/Coxhuang/glog.git
mkdir buildx && cd buildx
cmake -DBUILD_SHARED_LIBS=ON ..
make -j4 
sudo make install
```

2. 使用

> Cmake

```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(Glog REQUIRED libglog)
include_directories(
    ${Glog_INCLUDE_DIRS}
)
link_directories (
    ${Glog_LIBRARY_DIRS}
)
target_link_libraries(${TARGET_NAME}
    ${Glog_LIBRARIES}
)
```