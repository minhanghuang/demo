#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

struct Point {
  double x;
  double y;
};

int main(int argc, char* argv[]) {
  std::cout << "计算凸多边形最小外接矩形" << std::endl;

  // https://lbs.amap.com/demo/javascript-api/example/overlayers/polygon-draw-and-edit

  // 输入多边形的顶点
  std::vector<Point> points = {
      {116.403322, 39.920255},
      {116.410703, 39.897555},
      {116.402292, 39.892353},
      {116.389846, 39.891365},
  };

  // 将点转换为 OpenCV 需要的格式
  std::vector<cv::Point2f> cvPoints;
  for (const auto& p : points) {
    cvPoints.emplace_back(p.x, p.y);
  }

  // 计算最小外接矩形
  cv::RotatedRect minRect = cv::minAreaRect(cvPoints);

  // 提取矩形的四个顶点
  cv::Point2f rect_points[4];
  minRect.points(rect_points);

  // 输出最小外接矩形的顶点
  std::cout << "最小外接矩形的顶点：" << std::endl;
  for (int i = 0; i < 4; ++i) {
    std::cout << "[" << rect_points[i].x << ", " << rect_points[i].y << "]"
              << std::endl;
  }

  return 0;
}
