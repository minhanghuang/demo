#! /usr/bin/env python
#coding=utf-8
import pty
import os
import select

if __name__ == "__main__":

    master, slave = pty.openpty()
    slave_name = os.ttyname(slave)
    print("device name: {}".format(slave_name))
    while True:
        rl, wl, el = select.select([master], [], [], 1)
        for client in rl:
            data = os.read(client, 128)
            print("receive: {}".format(data))
            os.write(client, data)

