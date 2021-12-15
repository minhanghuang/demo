import psutil


class CPU(object):

    def __init__(self):
        pass


if __name__ == '__main__':

    print("Hello CPU!")
    for proc in psutil.process_iter():
        try:
            pinfo = proc.as_dict(attrs=['pid', 'name'])
        except psutil.NoSuchProcess:
            pass
        else:
            print(pinfo)


