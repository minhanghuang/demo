#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

struct Vehicle {
  double x;
  double y;
  double yaw;
  int position = -1;  // 初始位置
};

std::unordered_map<std::string, Vehicle> vehicles;

void UpdatePositions() {
  // Step 1: 找到 position == 0 的目标车辆
  std::string targetVehicleId;
  bool found = false;
  for (const auto& pair : vehicles) {
    if (pair.second.position == 0) {
      targetVehicleId = pair.first;
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "No vehicle with position == 0 found." << std::endl;
    return;
  }

  Vehicle& targetVehicle = vehicles[targetVehicleId];

  // Step 2: 计算所有车辆的相对位置和距离
  std::vector<std::pair<std::string, double>> scores;
  for (const auto& pair : vehicles) {
    if (pair.first == targetVehicleId) {
      continue;  // Skip the target vehicle itself
    }

    const Vehicle& vehicle = pair.second;
    // 计算相对坐标
    const double relative_x = vehicle.x - targetVehicle.x;
    const double relative_y = vehicle.y - targetVehicle.y;
    // 计算旋转后的坐标
    const double cos_yaw = std::cos(-targetVehicle.yaw);
    const double sin_yaw = std::sin(-targetVehicle.yaw);
    const double rotated_x = cos_yaw * relative_x - sin_yaw * relative_y;
    if (rotated_x < 0) {
      // 计算距离(score),距离越近分数越高
      double distance =
          std::sqrt(relative_x * relative_x + relative_y * relative_y);
      if (0 == distance) {
        scores.push_back({pair.first, std::numeric_limits<double>::max()});
      } else {
        scores.push_back({pair.first, 1 / distance});
      }
    }
  }

  // Step 3: 对车辆进行排序
  std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;  // 高分靠前
  });

  // Step 4: 计算position
  for (int i = 0; i < scores.size(); i++) {
    const Vehicle& vehicle = vehicles[scores.at(i).first];
    vehicles[scores.at(i).first].position = i + 1;
  }

  // 确保目标车辆位置为 0
  vehicles[targetVehicleId].position = 0;
}

void PrintVehicles() {
  for (const auto& pair : vehicles) {
    std::cout << "id:" << pair.first << "  position = " << pair.second.position
              << std::endl;
  }

  std::cout << "---" << std::endl;
}

int main() {
  // 示例：初始化车辆数据
  {
    vehicles.clear();
    vehicles["car0"] = {0.0, 50.0, M_PI_2, 0};   // 目标车辆
    vehicles["car1"] = {0.0, 51.0, M_PI_2, -1};  // 前
    vehicles["car2"] = {0.0, 52.0, M_PI_2, -1};  // 前
    vehicles["car3"] = {0.0, 53.0, M_PI_2, -1};  // 前
    vehicles["car4"] = {0.0, 54.0, M_PI_2, -1};  // 前
    // 更新 positions
    UpdatePositions();
    // 打印结果
    PrintVehicles();
    assert(vehicles["car0"].position == 0);
    assert(vehicles["car1"].position == -1);
    assert(vehicles["car2"].position == -1);
    assert(vehicles["car3"].position == -1);
    assert(vehicles["car4"].position == -1);
  }

  {
    vehicles.clear();
    vehicles["car0"] = {0.0, 50.0, M_PI_2, 0};   // 目标车辆
    vehicles["car1"] = {0.0, 41.0, M_PI_2, -1};  // 后
    vehicles["car2"] = {0.0, 42.0, M_PI_2, -1};  // 后
    vehicles["car3"] = {0.0, 43.0, M_PI_2, -1};  // 后
    vehicles["car4"] = {0.0, 44.0, M_PI_2, -1};  // 后
    // 更新 positions
    UpdatePositions();
    // 打印结果
    PrintVehicles();
    assert(vehicles["car0"].position == 0);
    assert(vehicles["car1"].position == 4);
    assert(vehicles["car2"].position == 3);
    assert(vehicles["car3"].position == 2);
    assert(vehicles["car4"].position == 1);
  }

  {
    vehicles.clear();
    vehicles["car0"] = {0.0, 50.0, M_PI_2, 0};   // 目标车辆
    vehicles["car1"] = {0.0, 49.0, M_PI_2, -1};  // 后
    vehicles["car2"] = {0.0, 52.0, M_PI_2, -1};  // 前
    vehicles["car3"] = {0.0, 44.0, M_PI_2, -1};  // 后
    vehicles["car4"] = {0.0, 54.0, M_PI_2, -1};  // 前
    // 更新 positions
    UpdatePositions();
    // 打印结果
    PrintVehicles();
    assert(vehicles["car0"].position == 0);
    assert(vehicles["car1"].position == 1);
    assert(vehicles["car2"].position == -1);
    assert(vehicles["car3"].position == 2);
    assert(vehicles["car4"].position == -1);
  }
  return 0;
}
