#include <tinyxml2.h>

#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello XML Write." << std::endl;
  const std::string file_path = "example.xml";

  // 创建一个XML文档
  tinyxml2::XMLDocument doc;

  // 创建一个根元素
  tinyxml2::XMLElement* root = doc.NewElement("OpenDRIVE");
  doc.InsertFirstChild(root);

  {
    // 创建一个子元素，并设置其文本内容
    tinyxml2::XMLElement* header = doc.NewElement("header");
    // header->SetText("Hello, World!");

    // 给子元素添加属性
    header->SetAttribute("revMajor", "1");
    header->SetAttribute("revMinor", "4");
    header->SetAttribute("name", "");
    header->SetAttribute("version", "1");
    header->SetAttribute("date", "2019-04-06T10:38:28");
    header->SetAttribute("north", "12.8349990809409476e+1");
    header->SetAttribute("south", "-3.5690998535156251e+2");
    header->SetAttribute("east", "4.2268105762411665e+2");
    header->SetAttribute("west", "-2.8359911988457576e+1.0");
    header->SetAttribute("vendor", "VectorZero");

    // 将子元素添加到根元素中
    root->InsertEndChild(header);
  }

  {
    // 属性
    tinyxml2::XMLElement* road = doc.NewElement("road");
    road->SetAttribute("name", "Road 0");
    road->SetAttribute("length", "3.6360177306314796e+1");
    road->SetAttribute("id", "0");
    road->SetAttribute("junction", "-1");

    // 子元素
    tinyxml2::XMLElement* link = doc.NewElement("link");
    tinyxml2::XMLElement* predecessor = doc.NewElement("predecessor");
    tinyxml2::XMLElement* successor = doc.NewElement("successor");
    predecessor->SetAttribute("elementType", "road");
    predecessor->SetAttribute("elementId", "11");
    predecessor->SetAttribute("contactPoint", "start");
    link->InsertEndChild(predecessor);
    successor->SetAttribute("elementType", "junction");
    successor->SetAttribute("elementId", "43");
    link->InsertEndChild(successor);

    road->InsertEndChild(link);

    root->InsertEndChild(road);
  }

  {
    // 添加XML声明(可选)
    tinyxml2::XMLDeclaration* declaration =
        doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(declaration);
  }

  // 将XML文档保存到文件中
  doc.SaveFile(file_path.c_str());

  return 0;
}
