import socket





if __name__ == '__main__':
    print("UDP Server")

    BUFSIZE = 1024
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    while True:
        msg = input(">> ").strip()
        ip_port = ('127.0.0.1', 8787)
        client.sendto(msg.encode('utf-8'), ip_port)

        data, server_addr = client.recvfrom(BUFSIZE)
        print('客户端recvfrom ', data,list(data))

    client.close()