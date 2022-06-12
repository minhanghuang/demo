from time import sleep
import serial


if __name__ == "__main__":
    # 'COM7', 3000000, bytesize=8, parity='N', stopbits=1
    ser = serial.Serial('/dev/pts/7', 115200)
    flag = ser.is_open

    if flag:
        data = "aa44121c960500402c000000c7b4a40810bc9f1b000000000000f5020000000032000000000000009a99993f9c6a39e7c449833f40fd3a09e07366c0abc8739f5f868f3f0000000069cd2746"
        data_hex = ""
        for i in range(0, len(data), 2):
            data_hex += "\\x" + data[i:i+2]
        while True:
            ser.write(data_hex)
            sleep(0.5)
            print("send")
        ser.close()
    else:
        print('Open Error\n')
