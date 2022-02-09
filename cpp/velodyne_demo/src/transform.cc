#include "transform.h"

VelodyneParser::VelodyneParser(const std::string& yaml_path) {
  InitYaml(yaml_path);
}

void VelodyneParser::InitYaml(const std::string& path) {
  std::cout << "yaml file path:" << path << std::endl;
  YAML::Node yaml_node = YAML::LoadFile(path);
  if (yaml_node.IsNull()) {
    std::cout << "yaml 文件异常" << std::endl;
    exit(0);
  }
  num_lasers_ = yaml_node["num_lasers"].as<int>();
  distance_resolution_ = yaml_node["num_lasers"].as<float>();
  const YAML::Node& lasers = yaml_node["lasers"];

  for (int i = 0; i < num_lasers_; i++) {
    LaserCorrection correction{};
    auto laser_id = lasers[i]["laser_id"].as<int>();
    correction.rot_correction = lasers[i]["rot_correction"].as<float>();
    correction.vert_correction = lasers[i]["vert_correction"].as<float>();
    correction.dist_correction = lasers[i]["dist_correction"].as<float>();

    correction.dist_correction_x = lasers[i]["dist_correction_x"].as<float>();
    correction.dist_correction_y = lasers[i]["dist_correction_y"].as<float>();
    correction.vert_offset_correction = lasers[i]["vert_offset_correction"].as<float>();

    correction.focal_distance = lasers[i]["focal_distance"].as<float>();
    correction.focal_slope = lasers[i]["focal_slope"].as<float>();

    correction.cos_rot_correction = cosf(correction.rot_correction);
    correction.sin_rot_correction = sinf(correction.rot_correction);
    correction.cos_vert_correction = cosf(correction.vert_correction);
    correction.sin_vert_correction = sinf(correction.vert_correction);
    correction.laser_ring = 0;
    laser_corrections_kv_[laser_id] = correction;
  } // for
}

void VelodyneParser::ConvertCoordinate(float radius,
                                       int azimuth,
                                       const LaserCorrection& correction,
                                       PointXYZIHIRBS& pt) {
  radius += correction.dist_correction;
  // 三角函数
  float cos_w = correction.cos_vert_correction;
  float sin_w = correction.sin_vert_correction;

  float cos_a = cosine_table_[azimuth] * correction.cos_rot_correction +
                sine_table_[azimuth] * correction.sin_rot_correction;
  float sin_a = sine_table_[azimuth] * correction.cos_rot_correction -
                cosine_table_[azimuth] * correction.sin_rot_correction;

  float xy_adjust = correction.vert_offset_correction * sin_w;
  float x_adjust = correction.horiz_offset_correction * cos_a;
  float y_adjust = correction.horiz_offset_correction * sin_a;
  float z_adjust = correction.vert_offset_correction * cos_w;
  // 计算投影长度
  float xy_radius = radius * cos_w - xy_adjust;
  float x = fabs(xy_radius * sin_a - x_adjust);
  float y = fabs(xy_radius * cos_a + y_adjust);
  // 线性插值矫正x，y，z
  float radius_ajust_by_x =
      correction.two_pt_correction_available
      ? ((x - 2.4) / (25.04 - 2.4) - 1) *
        (correction.dist_correction - correction.dist_correction_x)
      : 0;
  float radius_ajust_by_y =
      correction.two_pt_correction_available
      ? ((y - 1.93) / (25.04 - 1.93) - 1) *
        (correction.dist_correction - correction.dist_correction_y)
      : 0;
  float x_coord =
      ((radius + radius_ajust_by_x) * cos_w - xy_adjust) * sin_a - x_adjust;
  float y_coord =
      ((radius + radius_ajust_by_y) * cos_w - xy_adjust) * cos_a + y_adjust;
  float z_coord = (radius + radius_ajust_by_y) * sin_w + z_adjust;
  // 坐标系旋转
  pt.x = y_coord;
  pt.y = -x_coord;
  pt.z = z_coord;
}

void VelodyneParser::CalcIntensity(float radius,
                                   int reflectivity,
                                   const LaserCorrection& correction,
                                   PointXYZIHIRBS& pt) {
  float focal_offset = 256 * std::pow(1 - correction.focal_distance / 13100,2);
  float focal_slope = correction.focal_slope;
  float intensity =
      reflectivity +
      focal_slope * std::abs(focal_offset - 256 * std::pow(1 - radius / 65535, 2));
  pt.intensity = std::max(
      static_cast<float>(correction.min_intensity),
      std::min(intensity, static_cast<float>(correction.max_intensity)));
}

bool VLP16Parser::PacketToPoint(RawPacket& pkt, pcl::PointCloud<PointXYZIHIRBS>& pc) {
  for (int block = 0; block < BLOCKS_PER_PACKET; block++) {
    int azimuth = pkt.blocks[block].azimuth; // 方位角
    for (int channel = 0; channel < CHANNELS_PER_BLOCK; channel++) {
      LaserCorrection& correction = laser_corrections_kv_[channel];
      float radius = pkt.blocks[block].data[channel].radius * distance_resolution_;
      int reflectivity = pkt.blocks[block].data[channel].reflectivity;
      PointXYZIHIRBS p;
      ConvertCoordinate(radius, azimuth, correction, p); // xyz
      CalcIntensity(radius, reflectivity, correction, p); // intensity
      p.ring = correction.laser_ring; // ring
      p.height = radius + correction.dist_correction; // height
      pc.points.emplace_back(p);
    }
  }
  if (packet_count_ >= 75) {
    packet_count_ = 0;
    return true;
  }
  packet_count_++;
  return false;
}

VLP16Parser::VLP16Parser(const std::string& yaml_path)
  : VelodyneParser(yaml_path){

}