#include <algorithm>
#include <cmath>
#include <iostream>
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
    const double cos_yaw = cos(-targetVehicle.yaw);
    const double sin_yaw = sin(-targetVehicle.yaw);
    const double rotated_x = cos_yaw * relative_x - sin_yaw * relative_y;

    // 计算距离（score），距离越近分数越高
    double distance = sqrt(relative_x * relative_x + relative_y * relative_y);
    double score = (rotated_x > 0) ? (1 / distance) : (0);

    // 将车辆的 ID 和计算出的 score 存入向量中
    scores.push_back({pair.first, score});
  }

  // Step 3: 对车辆进行排序
  std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;  // 高分靠前
  });

  // Step 4: 更新车辆的 position 值
  int positionIndex = 1;  // 从 1 开始递增位置
  for (const auto& score : scores) {
    const Vehicle& vehicle = vehicles[score.first];
    const double relative_x = vehicle.x - targetVehicle.x;
    const double cos_yaw = cos(-targetVehicle.yaw);
    const double sin_yaw = sin(-targetVehicle.yaw);
    const double rotated_x =
        cos_yaw * relative_x - sin_yaw * (vehicle.y - targetVehicle.y);

    if (rotated_x > 0) {
      vehicles[score.first].position = -1;  // 前方车辆
    } else {
      vehicles[score.first].position = positionIndex++;  // 后方车辆，递增位置
    }
  }

  // 确保目标车辆位置为 0
  vehicles[targetVehicleId].position = 0;
}

int main() {
  // 示例：初始化车辆数据
  vehicles["car1"] = {100.0, 50.0, 0.0, 0};   // 目标车辆
  vehicles["car2"] = {110.0, 50.0, 0.2, -1};  // 在目标车辆前方
  vehicles["car3"] = {90.0, 50.0, -0.1, -1};  // 在目标车辆后方
  vehicles["car4"] = {105.0, 48.0, 0.3, -1};  // 在目标车辆前方
  vehicles["car5"] = {85.0, 52.0, -0.2, -1};  // 在目标车辆后方

  // 更新 positions
  UpdatePositions();

  // 打印结果
  for (const auto& pair : vehicles) {
    std::cout << "id:" << pair.first << "  position = " << pair.second.position
              << std::endl;
  }
  return 0;
}
