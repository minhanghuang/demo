import threading
import time


class Thread1(threading.Thread):
    def run(self):
        print("Thread1")
        time.sleep(1)
        print("Thread1 end")


class Thread2(threading.Thread):
    def run(self):
        print("Thread2")
        time.sleep(3)
        print("Thread2 end")


def run():
    print("Thread3")
    time.sleep(4)
    print("Thread3 end")
    return None


if __name__ == '__main__':

    print("Thread ")
    t1 = Thread1()
    t2 = Thread2()
    t3 = threading.Thread(target=run)
    t1.start()
    t2.start()
    t3.start()