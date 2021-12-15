import psutil
import time
import queue

class CPU(object):

    def __init__(self):
        self.process_list = []

    def update_process(self):
        self.process_list.clear()
        for pid in psutil.pids():
            p = psutil.Process(pid)
            if p.pid > 1000 and p.status() == "running":
                try:
                    p.cpu_percent(None)
                    self.process_list.append(p)
                except Exception as e:
                    pass
        time.sleep(1)
        return None

    def get_process_cpu_percent(self):

        q = queue.PriorityQueue(10) # top 10 process

        for process in self.process_list:
            curr_percent = process.cpu_percent(None)
            if q.full():
                q.get()
            q.put([curr_percent, process.pid])

        print(q.qsize())
        while not q.empty():  # 不为空时候执行
            try:
                value = q.get()
                pro = psutil.Process(value[1])
                print("[pid]:{} [name]:{} [percent]:{}% [exe]:{}".format(pro.pid,pro.name(),value[0],pro.exe()))
            except Exception as e:
                print("Exception:",e)

        return None

if __name__ == '__main__':
    print("Hello CPU")
    cpu = CPU()
    while True:
        cpu.update_process()
        cpu.get_process_cpu_percent()

    # psutil API https://blog.csdn.net/gymaisyl/article/details/101274862

