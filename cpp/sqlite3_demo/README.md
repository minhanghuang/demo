# SQLite3 C++

## #1 环境

```cpp
macOS
C++14
```

## #2 安装sqlite3

```cpp
git clone https://github.com/sqlite/sqlite.git
cd sqlite && mkdir bld && cd bld
../configure
make
make sqlite3.c
make test
sudo make install
```