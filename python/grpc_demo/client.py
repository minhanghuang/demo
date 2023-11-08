import grpc
from proto import calculator_pb2
from proto import calculator_pb2_grpc


def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = calculator_pb2_grpc.CalculatorStub(channel)

    add_request = calculator_pb2.AddRequest(num1=10, num2=5)
    add_response = stub.Add(add_request)
    print(f'Add result: {add_response.result}')

    subtract_request = calculator_pb2.SubtractRequest(minuend=10, subtrahend=5)
    subtract_response = stub.Subtract(subtract_request)
    print(f'Subtract result: {subtract_response.result}')


if __name__ == '__main__':
    run()
