import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    np.random.seed(42)    #设置随机种子，以方便之后的结果复现
    x = np.random.randn(30)   #生成30个随机参数并复制给变量x
    plt.plot(x, "r--o")        #将该30个随机参数以点的方式绘制出来并用线条进行连接，参数r--o用于在线型图中标记每个参数点的使用的形状、连接参数点使用的线条颜色和线性
    plt.show()
