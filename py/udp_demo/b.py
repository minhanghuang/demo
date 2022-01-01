#!/usr/bin/python python
# -*- coding:UTF-8 -*-
# UDP广播发送
from socket import *

HOST = '192.168.3.255'
# HOST = '<broadcast>'
PORT = 6681
BUFSIZE = 1024
ADDR = (HOST, PORT)

broadcast = socket(AF_INET, SOCK_DGRAM)
broadcast.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
while True:
    data = "00000"
    if not data:
        break
    print("send: %s" % data)
    broadcast.sendto(data.encode('utf-8'), ADDR)

broadcast.close()

