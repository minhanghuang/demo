import tornado.options
import tornado.web
import tornado.ioloop
import tornado.httpserver
import asyncio
from base import RequestHandlerBase
from base import WebSocketHandlerBase


class OkAPI(RequestHandlerBase):

    def get(self):

        self.response({
            "success": True,
            "msg": "ok",
            "results": None
        }, status=200)

    def post(self, *args, **kwargs):

        req = self.get_request()
        print("request data:{}".format(req))

        self.response({
            "success": True,
            "msg": "ok",
            "results": None
        }, status=200)


class WebSocketAPI(WebSocketHandlerBase):

    def open(self, *args, **kwargs):
        """
        新进来的用户, 钩子函数
        :param args:
        :param kwargs:
        :return: pass
        """

        self.user_pool.add(self)
        print("open user count:{}".format(len(self.user_pool)))

    def on_close(self):
        """
        客户端down后, 回调函数
        :return: pass
        """

        self.user_pool.remove(self)
        print("close user count:{}".format(len(self.user_pool)))

    def on_pong(self, data):

        for user in self.user_pool:
            user.write_message({"msg": "ws"})


if __name__ == '__main__':

    print("Hello Tornado!")
    tornado.options.parse_command_line()  # 允许命令行
    asyncio.set_event_loop(asyncio.new_event_loop())  # 多线程启动Tornado时,需要加上这一行
    app = tornado.web.Application([
        (r"/api/ok/", OkAPI),
        (r"/api/ws/", WebSocketAPI),
    ],
        debug=True,
        websocket_ping_interval=1 / 5,
        websocket_ping_timeout=1000,
    )
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(9090)
    tornado.ioloop.IOLoop.current().start()
