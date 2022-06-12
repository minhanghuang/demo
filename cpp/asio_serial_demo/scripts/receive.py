#! /usr/bin/env python
import pty
import os
import select
from time import sleep

def main():
  sender, slave = pty.openpty()
  print(os.ttyname(slave))
  receiver, slave = pty.openpty()
  print(os.ttyname(slave))
  data = "aa44121c960500402c000000c7b4a40810bc9f1b000000000000f5020000000032000000000000009a99993f9c6a39e7c449833f40fd3a09e07366c0abc8739f5f868f3f0000000069cd2746"
  data_hex = ""
  for i in range(0, len(data), 2):
      data_hex += "\\x" + data[i:i+2]

  print(data_hex)
  while True:
    # data = os.read(sender, 512)
    # print(data)
    # os.write(receiver, data)
    os.write(receiver, data_hex)
    sleep(0.5)

if __name__ == '__main__':
  main()
