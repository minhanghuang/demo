import logging

LOG_FORMAT = "[%(levelname)s] [%(asctime)s] [%(filename)s:%(lineno)d]- %(message)s"

logging.basicConfig(filename='my.log', level=logging.INFO, format=LOG_FORMAT)


if __name__ == '__main__':
    print("log")
    logging.info("This is a info log.")


