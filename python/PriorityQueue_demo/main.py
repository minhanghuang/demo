import queue

if __name__ == '__main__':

    q = queue.PriorityQueue(3)
    q.put([1, 'HaiCoder'])  # 1是级别最高的
    q.put([40, 1024])
    q.put([3, 'Python'])
    if q.full():
        q.get()
    q.put([5, True])
    if __name__ == '__main__':

        while not q.empty():  # 不为空时候执行
            print("get data =", q.get())