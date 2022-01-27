import paramiko


class SSH(object):

    def __init__(self, hostname: str, port: int, username: str, password: str):
        self.hostname = hostname
        self.port = port
        self.username = username
        self.password = password
        self.ssh = paramiko.SSHClient()
        self.know_host = paramiko.AutoAddPolicy()
        self.ssh.set_missing_host_key_policy(self.know_host)
        self.ssh.connect(
            hostname=self.hostname,
            port=self.port,
            username=self.username,
            password=self.password
        )

    def exec_cmd(self, cmd):
        return self.ssh.exec_command(cmd)


if __name__ == '__main__':
    print("Hello SSH")
    ssh = SSH(
        hostname="127.0.0.1",
        port=6789,
        username="trunk",
        password="123",
    )
    ssh.exec_cmd("mkdir -p /home/trunk/haha")
    # ssh.exec_cmd("echo '123' | sudo mkdir -p /opt/haha")

