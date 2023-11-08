import grpc
from concurrent import futures
from proto import calculator_pb2
from proto import calculator_pb2_grpc


class CalculatorServicer(calculator_pb2_grpc.CalculatorServicer):
    def Add(self, request, context):
        result = request.num1 + request.num2
        print("add function: {} + {} = {}".format(request.num1, request.num2, result))
        return calculator_pb2.AddResponse(result=result)

    def Subtract(self, request, context):
        result = request.minuend - request.subtrahend
        print("subtract function: {} - {} = {}".format(request.minuend,
              request.subtrahend, result))
        return calculator_pb2.SubtractResponse(result=result)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    addr = "[::]:50051"
    print("addr: {}".format(addr))
    calculator_pb2_grpc.add_CalculatorServicer_to_server(
        CalculatorServicer(), server)
    server.add_insecure_port(addr)
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    serve()
