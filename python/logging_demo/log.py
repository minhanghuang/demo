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
        info_handler = logging.handlers.TimedRotatingFileHandler(
            os.path.join(self.file_path, "info.log"),"midnight",1,30
        )
        error_handler = logging.handlers.TimedRotatingFileHandler(
            os.path.join(self.file_path, "error.log"),"midnight",1,30
        )
        console_handler = logging.StreamHandler()

        formatter = logging.Formatter('[%(levelname)s] [%(asctime)s] [%(filename)s] [Line:%(lineno)d] - %(message)s')

        info_handler.suffix = "%Y%m%d"  # 压缩文件后缀
        info_handler.setLevel(logging.INFO)
        info_handler.setFormatter(formatter)
        error_handler.suffix = "%Y%m%d"  # 压缩文件后缀
        error_handler.setLevel(logging.ERROR)
        error_handler.setFormatter(formatter)
        console_handler.setLevel(logging.DEBUG)
        console_handler.setFormatter(formatter)

        self.addHandler(info_handler)
        self.addHandler(error_handler)
        self.addHandler(console_handler)

        return None

log = Logger("log_test")