#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
  std::cout << "Hello, OpenCV." << std::endl;

  const std::string cat_image = "images/car.jpg";
  // {
  //   std::cout << "@@@@@ 展示一张图片 @@@@@" << std::endl;
  //   // 读取图像文件
  //   cv::Mat image = cv::imread(cat_image);

  //   // 检查图像是否成功加载
  //   if (image.empty()) {
  //     std::cerr << "无法加载图像" << std::endl;
  //     return -1;
  //   }

  //   // 在这里你可以对图像进行各种处理

  //   // 显示图像
  //   cv::imshow("Loaded Image", image);

  //   // 等待用户按下键盘任意键后关闭窗口
  //   cv::waitKey(0);

  //   // 释放图像资源
  //   cv::destroyAllWindows();
  // }

  {
    std::cout << "@@@@@ 读取照片数据 @@@@@" << std::endl;
    std::ifstream image_file(cat_image, std::ios::binary);
    if (!image_file) {
      std::cerr << "无法打开图像文件" << std::endl;
      return -1;
    }
    // 读取文件数据到std::vector<unsigned char>
    std::vector<unsigned char> image_buffer(
        (std::istreambuf_iterator<char>(image_file)),
        (std::istreambuf_iterator<char>()));

    // 使用cv::imdecode将图像数据解码为cv::Mat
    cv::Mat image = cv::imdecode(image_buffer, cv::IMREAD_COLOR);

    // 检查图像是否成功加载
    if (image.empty()) {
      std::cerr << "无法加载图像" << std::endl;
      return -1;
    }

    // 显示图像
    cv::imshow("Loaded Image", image);

    // 等待用户按下键盘任意键后关闭窗口
    cv::waitKey(0);

    // 释放图像资源
    cv::destroyAllWindows();
  }
  return 0;
}
