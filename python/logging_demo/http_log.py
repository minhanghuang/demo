import os
import logging
import logging.handlers


class Logger(logging.Logger):

    def __init__(self, name: str):
        super().__init__(name)
        self.file_path = "/var/log/trunk/py_log"
        if not os.path.exists(self.file_path):
            os.makedirs(self.file_path)

        self.register_logging()

    def register_logging(self):
        info_handler = logging.handlers.HTTPHandler(
            host="127.0.0.1:8888",
            url="/",
            method="POST"
        )
        console_handler = logging.StreamHandler()
        formatter = logging.Formatter('[%(levelname)s] [%(asctime)s] [%(filename)s] [Line:%(lineno)d] - %(message)s')

        info_handler.setFormatter(formatter)
        info_handler.setLevel(logging.INFO)

        console_handler.setFormatter(formatter)
        console_handler.setLevel(logging.DEBUG)

        self.addHandler(info_handler)
        self.addHandler(console_handler)

        return None


http_log = Logger("http_log")