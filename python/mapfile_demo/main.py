import json

class Map(object):

    def __init__(self, path):
        print("path:",path)
        self.path = path
        self.type = set()
        self.turnType = set()
        self.speedLimit = set()
        self.change = set()
        self.BorderType = set()
        self.BorderColor = set()

    def run(self):
        with open(self.path,"r",encoding='utf-8') as f:
            data = json.load(f)
        for roads in data["roads"]:
            for section in roads["laneSections"]:
                for lane in section["lanes"]:
                    # print(lane.keys())
                    self.type.add(lane["type"])
                    self.turnType.add(lane["turnType"])
                    self.speedLimit.add(lane["speedLimit"])
                    self.BorderType.add(lane["leftBorder"]["type"])
                    self.BorderColor.add(lane["leftBorder"]["color"])
                    self.BorderType.add(lane["rightBorder"]["type"])
                    self.BorderColor.add(lane["rightBorder"]["color"])

        print("type:",self.type)
        print("turnType:",self.turnType)
        print("speedLimit:",self.speedLimit)
        print("BorderType:",self.BorderType)
        print("BorderColor:",self.BorderColor)
        return None


if __name__ == '__main__':

    print("小地图 build..")
    m = Map("/Users/cox/work/office/5.地图文件/6.小地图/Town01.json")
    m.run()

