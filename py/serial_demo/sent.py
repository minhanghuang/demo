import serial 


if __name__ == "__main__":
    ser = serial.Serial('/dev/pts/2', 115200, 8, 'N', 1) # 'COM7', 3000000, bytesize=8, parity='N', stopbits=1
    flag = ser.is_open

    if flag:
        while True:
            data = raw_input("input: ")
            print("sent: {}".format(data))
            ser.write(data)
        ser.close()
    else:
        print('Open Error\n')
   
