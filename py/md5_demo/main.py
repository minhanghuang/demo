import hashlib
import os
import sys


def CalcMD5(filepath):
    with open(filepath, 'rb') as f:
        md5obj = hashlib.md5()
        md5obj.update(f.read())
        hash = md5obj.hexdigest()
        return hash


def main():
    if len(sys.argv) == 3:
        print("file1: {}".format(sys.argv[1]))
        print("file2: {}".format(sys.argv[2]))
        if os.path.exists(sys.argv[1]) and os.path.exists(sys.argv[2]) and CalcMD5(sys.argv[1]) == CalcMD5(sys.argv[2]):
            print("文件MD5值相等")
        else:
            print("文件MD5值不等")
    else:
        print("Used python3 main.py file1 fiel2")


if __name__ == "__main__":
    main()
