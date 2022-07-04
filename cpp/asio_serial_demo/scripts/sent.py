#! /usr/bin/env python
import pty
import os
import select
from time import sleep

def main():
  sender, slave = pty.openpty()
  print(os.ttyname(slave))
  # 1429
  data1 = "aa44121c9505004048000000c7b4a408b06d9e1b000000000000f50200000000100000002d4368c29e504540a66f4429b17e5b400ab4cf6bcf1e93401b06f5c13d0000003ecb893f03c6c33f3be7303f36383300cdcccc3f2ebd353c0c07070700003033adf08053aa44121c960500402c000000c7b4a408b06d9e1b000000000000f502000000003200000000000000cdcccc3f2e5f4fd3f5c8973f0876e5c0fe294a402e1d388c096ba2bf000000004757c3f4"
  # 971 
  data2 = "aa44121ccb0300402c000000c7b4a408b06d9e1b000000000000f5020000000000000000000000000000000000000000000000000000000000000000000000000b000b00000030335ea398c6aa44121c9505004048000000c7b4a408786e9e1b000000000000f502000000001000000022c7b5be9e504540cd811e27b17e5b400a33b3f9dc1e93401c06f5c13d000000e6ca893faec4c33f5de7303f363833006666e63f91393f3c0c07070700003033a8a03129"
  # 1430 
  data3 = "aa44121c960500402c000000c7b4a408786e9e1b000000000000f5020000000032000000000000006666e63f5d74547fd6c88a3f23649b096e4b5cc0ac14fdd543e09d3f00000000b83c034c"
  data_1 = ""
  data_2 = ""
  data_3 = ""
  for i in range(0, len(data1), 2):
      data_1 += " " + data1[i:i+2]
  for i in range(0, len(data2), 2):
    data_2 += " " + data2[i:i+2]
  for i in range(0, len(data3), 2):
    data_3 += " " + data3[i:i+2]
  data1_hex = bytes.fromhex(data_1)
  data2_hex = bytes.fromhex(data_2)
  data3_hex = bytes.fromhex(data_3)
  flag = 3
  while True:
    if flag == 3:
      os.write(sender, data1_hex)
      flag -= 1
    elif flag == 2:
      os.write(sender, data2_hex)
      flag -= 1
    elif flag == 1:
      os.write(sender, data3_hex)
      flag -= 1
    else:
      flag  = 3
    sleep(1)

if __name__ == '__main__':
  main()

