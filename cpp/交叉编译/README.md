```shell
sudo apt update
sudo apt install gcc-aarch64-linux-gnu
sudo apt install g++-aarch64-linux-gnu
```

```shell
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain.cmake ..
make -j$(nproc)
```

```shell
readelf -h libcat.so
```
