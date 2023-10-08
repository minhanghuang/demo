import requests

if __name__ == '__main__':

    while True:
        t = requests.get("https://www.baidu.com/")
        print(t.status_code)