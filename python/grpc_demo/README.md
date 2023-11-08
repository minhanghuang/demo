# Python gRPC

## 安装:

```shell
python3 -m pip install protobuf
python3 -m pip install grpcio grpcio-tools
```

## 生成grpc文件

```shell
python3 -m grpc_tools.protoc -I<proto文件路径> --python_out=<python文件输出路径> --grpc_python_out=<grpc文件输出路径> <proto文件>
# python3 -m grpc_tools.protoc -Iproto --python_out=proto --grpc_python_out=proto calculator.proto
```

