#include <tinyxml2.h>

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
  std::cout << "Hello XML." << std::endl;
  tinyxml2::XMLDocument r_doc;

  // 加载文件
  r_doc.LoadFile("test.xml");
  if (r_doc.Error()) {
    return -1;
  }

  // 获取根元素
  tinyxml2::XMLElement* root_ele = r_doc.RootElement();

  // 获取元素
  tinyxml2::XMLElement* header_ele =
      r_doc.FirstChildElement("OpenDRIVE")->FirstChildElement("header");
  if (header_ele) {
    std::cout << "has header element" << std::endl;
  } else {
    std::cout << "header element is null" << std::endl;
  }

  // 获取元素属性
  const tinyxml2::XMLAttribute* revmajor_attr =
      header_ele->FindAttribute("revMajor");
  if (revmajor_attr) {
    const char* revmajor_value = revmajor_attr->Value();
    std::cout << "revmAjor value: " << revmajor_value << std::endl;
  }
  const tinyxml2::XMLAttribute* north_attr = header_ele->FindAttribute("north");
  if (north_attr) {
    double north_value = north_attr->DoubleValue();
    std::stringstream s;
    s << std::setprecision(16) << north_value;
    std::cout << "north value: " << s.str() << std::endl;
  }

  // 获取元素文本
  const tinyxml2::XMLElement* georeference_ele =
      header_ele->FirstChildElement("geoReference");
  if (georeference_ele) {
    const char* georeference_text = georeference_ele->GetText();
    std::cout << "georeference text: " << georeference_text << std::endl;
  }

  // 遍历元素
  for (tinyxml2::XMLElement* curr_ele = header_ele->FirstChildElement();
       curr_ele; curr_ele = curr_ele->NextSiblingElement()) {
    std::cout << "element name:" << curr_ele->Name() << std::endl;
  }

  // 写入
  const std::string file_path = "xxx.xml";
  tinyxml2::XMLDocument w_doc;
  const char* declaration = "<?xml version=\"1.0\" standalone=\"yes\"?>";
  r_doc.Parse(declaration);
  tinyxml2::XMLElement* ele_root = r_doc.NewElement("OpenDRIVE");
  r_doc.InsertEndChild(ele_root);
  tinyxml2::XMLElement* ele_head = r_doc.NewElement("header");
  ele_root->InsertEndChild(ele_head);
  r_doc.SaveFile(file_path.c_str());

  return 0;
}
