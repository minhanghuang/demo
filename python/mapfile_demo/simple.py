import json

class TransformMap(object):

    def __init__(self, src_name, new_name, t="simple"):
        self.src_name = src_name
        self.new_name = new_name
        self.t = t

    def update_map_data(self):

        simple_data = {}

        with open(self.src_name,"r",encoding='utf-8') as f:
            data = json.load(f)

        for roads in data["roads"]:
            for section in roads["laneSections"]:
                for lanes in section["lanes"]:
                    lane = []
                    c_line = []
                    l_line = []
                    r_line = []
                    if self.t=="simple":
                        if "noTurn" == lanes["turnType"]:
                            c_line.append([lanes["centerLine"][0]["x"],lanes["centerLine"][0]["y"]])
                            c_line.append([lanes["centerLine"][-1]["x"],lanes["centerLine"][-1]["y"]])
                            lane.append(c_line)
                            l_line.append([lanes["leftBorder"]["pointSet"][0]["x"], lanes["leftBorder"]["pointSet"][0]["y"]])
                            l_line.append([lanes["leftBorder"]["pointSet"][-1]["x"], lanes["leftBorder"]["pointSet"][-1]["y"]])
                            lane.append(l_line)
                            r_line.append([lanes["rightBorder"]["pointSet"][0]["x"], lanes["rightBorder"]["pointSet"][0]["y"]])
                            r_line.append([lanes["rightBorder"]["pointSet"][-1]["x"], lanes["rightBorder"]["pointSet"][-1]["y"]])
                            lane.append(r_line)

                        else:
                            for line in lanes["centerLine"]:
                                c_line.append([line["x"],line["y"]])
                            lane.append(c_line)
                            for line in lanes["leftBorder"]["pointSet"]:
                                l_line.append([line["x"],line["y"]])
                            lane.append(l_line)
                            for line in lanes["rightBorder"]["pointSet"]:
                                r_line.append([line["x"],line["y"]])
                            lane.append(r_line)
                    else:
                        for line in lanes["centerLine"]:
                            c_line.append([line["x"], line["y"]])
                        lane.append(c_line)
                        for line in lanes["leftBorder"]["pointSet"]:
                            l_line.append([line["x"], line["y"]])
                        lane.append(l_line)
                        for line in lanes["rightBorder"]["pointSet"]:
                            r_line.append([line["x"], line["y"]])
                        lane.append(r_line)

                    simple_data[lanes["uid"]] = lane

        with open(self.new_name, 'wb') as f:
            f.write((json.dumps(simple_data).encode("utf-8")))

        return None


if __name__ == '__main__':
    print("simple map")
    transform = TransformMap("/Users/cox/work/office/5.地图文件/6.小地图/Town01.json","Town01.json","full")
    transform.update_map_data()