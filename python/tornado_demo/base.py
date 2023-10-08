from tornado import web
from tornado.websocket import WebSocketHandler
import json


class RequestHandlerBase(web.RequestHandler):

    def get_request(self):
        """
        获取 post request 数据
        :return: dict
        """

        request_str = self.request.body.decode('utf-8')
        if request_str:
            ret = json.loads(request_str)
        else:
            ret = dict()

        return ret

    def response(self, data=None, status=200):
        """
        返回值(重写)
        :param data: 返回数据
        :param status: 状态码, 默认200
        :return: None
        """
        self.set_status(status)
        self.write(data)

        return None

    def set_default_headers(self):
        """
        解决跨域(重写) - 1
        :return: None
        """

        self.set_header('Access-Control-Allow-Origin', '*')
        self.set_header('Access-Control-Allow-Headers', '*')
        self.set_header('Access-Control-Max-Age', 1000)
        self.set_header('Content-type', 'application/json')
        self.set_header('Access-Control-Allow-Methods', 'POST, GET, OPTIONS')
        self.set_header('Access-Control-Allow-Headers',  # '*')
                        'authorization, Authorization, Content-Type, Access-Control-Allow-Origin, Access-Control-Allow-Headers, X-Requested-By, Access-Control-Allow-Methods')

        return None

    def options(self):
        """
        解决跨域(重写) - 2
        :return:
        """

        pass

    def on_finish(self):
        """
        tornado web 请求结束 拦截器(重写)
        :return: NOne
        """

        return None

    def set_logging(self):
        """
        将请求写入日志
        :return: None
        """

        request = self.request
        status = self.get_status()
        if status >= 200 and status <= 299:
            pass
        else:
            pass

        return None

    def log_exception(self, typ, value, tb):
        """
        tornado 异常拦截器
        :param typ: exception class
        :param value: exception massage
        :param tb: exception object
        :return:
        """
        return None


class WebSocketHandlerBase(WebSocketHandler):

    user_pool = set()

    def __init__(self, application, request, **kwargs):
        super().__init__(application, request, **kwargs)

    def open(self, *args, **kwargs):
        """
        新进来的用户
        :param args:
        :param kwargs:
        :return:
        """
        pass

    def on_message(self, message):
        """
        客户端发来的数据, 钩子函数
        :param message: 客户端传来的数据
        :return: None
        """

        pass

    def on_pong(self, data):
        """
        服务端向客户端发送ping帧, 客户端回调函数 (客户端online->回调; 客户端down时->不进入回调)
        :param data: 服务端发送的ping帧数据, 默认ping帧为空
        :return: None
        """

        pass

    def on_ping(self, data):
        """
        服务端接收客户端发来的ping帧
        :param data: 客户端发来的ping帧数据
        :return: None
        """

        pass

    def check_origin(self, origin):
        """
        是否允许跨域
        :param origin:
        :return: bool (True:允许; False:不允许)
        """

        return True

    def on_close(self):
        """
        :return: None
        """
        pass

    def log_exception(self, typ, value, tb):
        """
        tornado 异常拦截器
        :param typ: exception class
        :param value: exception massage
        :param tb: exception object
        :return:
        """

        return None