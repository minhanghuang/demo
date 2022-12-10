import xml.etree.ElementTree as ET


if __name__ == "__main__":
    tree = ET.parse("oxrd.xml")
    root = tree.getroot()
    left_boundarys = []
    right_boundarys = []
    reference_lines = []
    for child in root:
        if child.tag == "road":
            for section in child:
                for lane in section:
                    if lane.tag == "lane":
                        for line in lane:
                            print(line.tag)
                            if line.tag == "left_boundary":
                                left_boundary = []
                                for point in line:
                                    left_boundary.append(
                                        [point.attrib.get("x"), point.attrib.get("y")])
                                left_boundarys.append(left_boundary)
                            elif line.tag == "right_boundary":
                                right_boundary = []
                                for point in line:
                                    right_boundary.append(
                                        [point.attrib.get("x"), point.attrib.get("y")])
                                right_boundarys.append(right_boundary)
                    if lane.tag == "reference_line":
                        reference_line = []
                        for point in lane:
                            reference_line.append(
                                [point.attrib.get("x"), point.attrib.get("y")])
                        reference_lines.append(reference_line)

    print(left_boundarys)
    print(right_boundarys)
    print(reference_lines)
