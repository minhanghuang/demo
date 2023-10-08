from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import ThreadedFTPServer

class MyFTPHandler(FTPHandler):

    def on_connect(self):
        print("on_connect",dir(self.dtp_handler))


    def process_command(self, *args, **kwargs):
        # increase counter for every received command
        print("0000000",args[0], args[1])
        FTPHandler.process_command(self, *args, **kwargs)



class MyFTPServer(object):

    def __init__(self, port, path, username, password, perm):
        self.port = port
        self.path = path
        self.username = username
        self.password = password
        self.perm = perm
        self.authorizer = DummyAuthorizer()
        self.authorizer.add_user(self.username, self.password, self.path, self.perm)
        self.handler = MyFTPHandler
        self.handler.authorizer = self.authorizer
        self.server = ThreadedFTPServer(('0.0.0.0', self.port), self.handler)
        print("username:{} password:{}".format(self.username,self.password))

    def run(self):
        self.server.serve_forever()
        return None


if __name__ == '__main__':

    server = MyFTPServer(
        port=8080,
        path="/",
        username="mapdev",
        password="123",
        perm="elradfmw",
    )
    server.run()