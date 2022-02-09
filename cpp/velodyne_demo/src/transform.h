#ifndef VELODYNE_DEMO_TRANSFORM_H_
#define VELODYNE_DEMO_TRANSFORM_H_
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <math.h>

#include <yaml-cpp/yaml.h>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <rosbag/query.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/impl/pcl_base.hpp>
#include <velodyne_msgs/VelodynePacket.h>
#include <velodyne_msgs/VelodyneScan.h>


static const int VLP16_PACKETS_PER_FRAME = 76;
static const int VLP32C_PACKETS_PER_FRAME = 151;
static const int PACKET_SIZE = 1206;
static const int BLOCKS_PER_PACKET = 12;
static const int CHANNELS_PER_BLOCK = 32;
static const int RAW_SCAN_SIZE = 3;

static const float ROTATION_RESOLUTION = 0.01f;     // [deg]
static const uint16_t ROTATION_MAX_UNITS = 36000u;  // [deg/100]
static const float FULL_FIRING_CYCLE = 55.296 * 1e-6;
static const float SINGLE_FIRING = 2.304 * 1e-6;

static const uint16_t BLOCK_FLAG_HEADER = 0xeeff;

inline uint16_t bytes_to_uint16(const uint8_t* bytes) {
  return (uint16_t)(bytes[0] + (bytes[1] << 8));
}

inline uint32_t bytes_to_uint32(const uint8_t* bytes) {
  return (uint32_t)(bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) +
                    (bytes[3] << 24));
}

/**
 * @brief: 激光矫正
 * */
struct LaserCorrection {
  float rot_correction;
  float vert_correction;
  float dist_correction;
  bool two_pt_correction_available;
  float dist_correction_x;
  float dist_correction_y;
  float vert_offset_correction;
  float horiz_offset_correction;
  int max_intensity;
  int min_intensity;
  float focal_distance;
  float focal_slope;
  /** cached values calculated when the calibration file is read */
  float cos_rot_correction;  ///< cosine of rot_correction
  float sin_rot_correction;  ///< sine of rot_correction
  float cos_vert_correction; ///< cosine of vert_correction
  float sin_vert_correction; ///< sine of vert_correction
  int laser_ring; ///< ring number for this laser
};

/**
 * @brief The VLP channel data struct
 */
struct RawChannel {
  uint16_t radius;
  uint8_t reflectivity;

  void set(const uint8_t* bytes) {
    radius = bytes_to_uint16(bytes);
    reflectivity = bytes[2];
  }
};

/**
 * @brief The VLP Block Data Structure
 */
struct RawBlock {
  uint16_t header;   ///< UPPER_BANK or LOWER_BANK
  uint16_t azimuth;  ///< 0-35999, divide by 100 to get degrees
  RawChannel data[32];

  void set(const uint8_t* bytes) {
    header = bytes_to_uint16(bytes);
    azimuth = bytes_to_uint16(bytes + 2);
    for (int i = 0; i < CHANNELS_PER_BLOCK; ++i) {
      data[i].set(bytes + 4 + i * RAW_SCAN_SIZE);
    }
  }
};

/**
 * @brief The VLP Packet Data Structure
 */
struct RawPacket {
  RawBlock blocks[12];
  uint32_t timestamp;
  uint8_t mode;
  uint8_t model;

  void set(const uint8_t* bytes) {
    for (int i = 0; i < BLOCKS_PER_PACKET; ++i) {
      blocks[i].set(bytes + i * 100);
    }
    timestamp = bytes_to_uint32(bytes + 1200);
    mode = bytes[1204];
    model = bytes[1205];
  }
};

/// 全量信息的点云（带height(高度),range(度量),ring(第几圈))
struct PointXYZIHIRBS {
  PCL_ADD_POINT4D;
  float height; // 高度
  float range; // 度量
  uint8_t intensity; // 强度
  uint8_t intensity_vi; // ??
  uint8_t ring; // 第几圈
  uint8_t type; // 类型

  inline PointXYZIHIRBS() {
    x = y = z = 0.0f;
    intensity = intensity_vi = ring = type = 0;
    height = range = 0.0f;
  }
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIHIRBS,
(float, x, x)(float, y, y)(float, z, z)(std::uint8_t, intensity, intensity)
(float, height, height)(std::uint8_t, intensity_vi, intensity_vi)
(float, range, range)(std::uint8_t, ring, ring)(std::uint8_t, type, type))


class VelodyneParser {
public:
  explicit VelodyneParser(const std::string& yaml_path);

protected:
  void InitYaml(const std::string& path);
  void ConvertCoordinate(float radius,
                         int azimuth,
                         const LaserCorrection& correction,
                         PointXYZIHIRBS& pt);
  void CalcIntensity(float radius,
                     int reflectivity,
                     const LaserCorrection& correction,
                     PointXYZIHIRBS& pt);

  std::unordered_map<int, LaserCorrection> laser_corrections_kv_;
  float distance_resolution_ = 0;
  int num_lasers_ = 0;
  float sine_table_[ROTATION_MAX_UNITS];
  float cosine_table_[ROTATION_MAX_UNITS];
  int packet_count_ = 0;

};

class VLP16Parser : public VelodyneParser {
public:
  explicit VLP16Parser(const std::string& yaml_path);
  bool PacketToPoint(RawPacket& pkt, pcl::PointCloud<PointXYZIHIRBS>& cloud);

};

#endif // VELODYNE_DEMO_TRANSFORM_H_
