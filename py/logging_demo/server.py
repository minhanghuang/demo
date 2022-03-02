import tornado.web
import tornado.ioloop


class IndexHandler(tornado.web.RequestHandler):

    def get(self):
        print("get")
        self.write("get")

    def post(self):
        print("post")
        print(str(self.request.body, encoding = "utf-8"))
        self.write("post ~")


if __name__ == '__main__':
    app = tornado.web.Application([(r'/', IndexHandler)])
    app.listen(8888)
    tornado.ioloop.IOLoop.current().start()
