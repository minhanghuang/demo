import requests
import os
import time




if __name__ == '__main__':
    print("get file")
    r = requests.get("http://192.168.199.4:8080/file/bags/hdmap.bag")
    with open("file.bag", "wb") as f:
        f.write(r.content)
