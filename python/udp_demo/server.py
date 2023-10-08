import socket


if __name__ == '__main__':
    print("UDP Server")

    BUFSIZE = 1024
    ip_port = ('127.0.0.1', 8787)
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.bind(ip_port)
    while True:
        data, client_addr = server.recvfrom(BUFSIZE)
        print('server收到的数据', data)
        server.sendto(data.upper(), client_addr)

    server.close()