#!/usr/bin/python python
# -*- coding:UTF-8 -*-
# UDP 广播接收
from socket import *

HOST = '0.0.0.0'
PORT = 6681
BUFSIZE = 1024

broadcastrecv = socket(AF_INET, SOCK_DGRAM)
broadcastrecv.bind((HOST, PORT))
print('wating...')
while True:
    data, addr = broadcastrecv.recvfrom(BUFSIZE)
    print('recv: %s %s' % (addr, data))

broadcastrecv.close()

