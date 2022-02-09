import subprocess


if __name__ == '__main__':
    print("Hello subprocess")
    subprocess.call("ssh trunk@172.16.87.3", shell=True)
    print("000000")
