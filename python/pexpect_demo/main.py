import pexpect
from pexpect.pxssh import pxssh


if __name__ == '__main__':
    print("Hello Pexpect")
    # child = pexpect.spawn('ssh trunk@172.16.87.3')
    # child.expect('password')
    # child.sendline('123')
    hostname = '172.16.87.3'
    user = 'trunk'
    password = '123'
    s = pxssh()
    s.login(hostname, user, password)
    s.sendline('ip addr')
    s.prompt()				# 匹配命令提示符
    print(s.before)			# 查看命令执行结果
    s.logout()