import argparse


class Parser:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(description='')
        self.parser.add_argument('-f', '--file', type=str, help='输入文件的路径')
        # action='store_true' 用于创建一个布尔型的命令行参数选项，它通常用于标志是否启用某个功能或选项。
        self.parser.add_argument(
            '-v', '--verbose', action='store_true', help='启用详细日志输出')
        self.args = self.parser.parse_args()

    def get_file(self):
        return self.args.file

    def get_verbose(self):
        return self.args.verbose


def main():
    parser = Parser()
    print("file: {}".format(parser.get_file()))
    print("verbose: {}".format(parser.get_verbose()))
    # python3 main.py -f /opt/xodr -v
    #   file: /opt/xodr
    #   verbose: True

    # python3 main.py -f /opt/xodr
    #   file: /opt/xodr
    #   verbose: False

    # python3 main.py
    #   file: None
    #   verbose: False


if __name__ == "__main__":
    main()
