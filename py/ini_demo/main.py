import configparser


def main():
    pass
    config = configparser.ConfigParser()
    config.read("start.ini")
    for section in config.sections():
        print(section)
        for (key, val) in config.items(section):
            print("{}={} ...".format(key, val))


if __name__ == "__main__":
    main()
