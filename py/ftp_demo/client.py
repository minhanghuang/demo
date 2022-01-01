from ftplib import FTP


class MyFTP(object):

    def __init__(self, host, port, username, password):
        self.host = host
        self.port = port
        self.username = username
        self.password = password
        self.bufsize = 1024
        self.ftp = FTP()
        self.connect()
        print("username:{} password:{}".format(self.username,self.password))

    def connect(self):
        self.ftp.connect(self.host, self.port)
        self.ftp.login(self.username, self.password)
        return self.ftp

    def get(self, local_path, remote_path):
        fp = open(local_path, 'wb')
        self.ftp.retrbinary('RETR ' + remote_path, fp.write, self.bufsize)
        self.ftp.set_debuglevel(0)  # 参数为0，关闭调试模式
        fp.close()

        return None

    def update(self, local_path, remote_path):
        fp = open(local_path, 'rb')
        self.ftp.storbinary('STOR ' + remote_path, fp, self.bufsize)
        self.ftp.set_debuglevel(0)
        fp.close()

        return None


if __name__ == "__main__":
    ftp_obj = MyFTP(
        host="127.0.0.1",
        port=8080,
        username="mapdev",
        password="123",
    )
    ftp_obj.get(local_path=r"/Users/cox/Downloads/ftp/haha.bag", remote_path="opt/file/bags/hdmap.bag")
    print(ftp_obj.ftp.getwelcome())
