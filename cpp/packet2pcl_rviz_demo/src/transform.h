#ifndef PACKET2PCL_RVIZ_DEMO_TRANSFORM_H_
#define PACKET2PCL_RVIZ_DEMO_TRANSFORM_H_
#include <cmath>
#include <iostream>
#include <unordered_map>

#include <pcl/impl/pcl_base.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <ros/ros.h>
#include <velodyne_msgs/VelodynePacket.h>
#include <velodyne_msgs/VelodyneScan.h>
#include <yaml-cpp/yaml.h>

static const int VLP16_PACKETS_PER_FRAME = 76;
static const int VLP32C_PACKETS_PER_FRAME = 151;
static const int PACKET_SIZE = 1206;
static const int BLOCKS_PER_PACKET = 12;
static const int VLP16_FIRINGS_PER_BLOCK = 2;
static const int VLP16_SCANS_PER_FIRING = 16;
static const int CHANNELS_PER_BLOCK = 32;
static const int RAW_SCAN_SIZE = 3;

static const float ROTATION_RESOLUTION = 0.01f;   // [deg]
static const uint16_t ROTATION_MAX_UNITS = 36000u;// [deg/100]
static const float FULL_FIRING_CYCLE = 55.296 * 1e-6;
static const float SINGLE_FIRING = 2.304 * 1e-6;
static const float VLP16_BLOCK_TDURATION = 110.592f;// [µs]
static const float VLP16_DSR_TOFFSET = 2.304f;      // [µs]
static const float VLP16_FIRING_TOFFSET = 55.296f;  // [µs]


/// 全量信息的点云（带height,range,ring)
struct PointXYZIHIRBS {
    PCL_ADD_POINT4D;
    uint8_t intensity;
    uint8_t ring;
    inline PointXYZIHIRBS() {
        x = y = z = 0.0f;
        intensity = ring = 0;
    }
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIHIRBS,
                                  (float, x, x) (float, y, y) (float, z, z) (std::uint8_t, intensity, intensity) (std::uint8_t, ring, ring))


inline uint16_t bytes_to_uint16(const uint8_t *bytes) {
    return (uint16_t) (bytes[0] + (bytes[1] << 8));
}

inline uint32_t bytes_to_uint32(const uint8_t *bytes) {
    return (uint32_t) (bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) +
                       (bytes[3] << 24));
}

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
    float cos_rot_correction; ///< cosine of rot_correction
    float sin_rot_correction; ///< sine of rot_correction
    float cos_vert_correction;///< cosine of vert_correction
    float sin_vert_correction;///< sine of vert_correction
    int laser_ring;           ///< ring number for this laser
};

/**
 * @brief The VLP channel data struct
 */
struct RawChannel {
    uint16_t radius;
    uint8_t reflectivity;

    void set(const uint8_t *bytes) {
        radius = bytes_to_uint16(bytes);
        reflectivity = bytes[2];
    }
};

/**
 * @brief The VLP Block Data Structure
 */
struct RawBlock {
    uint16_t header; ///< UPPER_BANK or LOWER_BANK
    uint16_t azimuth;///< 0-35999, divide by 100 to get degrees
    RawChannel data[32];

    void set(const uint8_t *bytes) {
        header = bytes_to_uint16(bytes);
        azimuth = bytes_to_uint16(bytes + 2);
        for (int i = 0; i < 32; ++i) {
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

    void set(const uint8_t *bytes) {
        for (int i = 0; i < 12; ++i) {
            blocks[i].set(bytes + i * 100);
        }
        timestamp = bytes_to_uint32(bytes + 1200);
        mode = bytes[1204];
        model = bytes[1205];
    }
};

class LidarParser {
public:
    explicit LidarParser(const std::string &path);

protected:
    void ConvertCoordinate(float radius,
                           int azimuth,
                           const LaserCorrection &correction,
                           PointXYZIHIRBS &pt);
    void CalcIntensity(float radius,
                       int reflectivity,
                       const LaserCorrection &correction,
                       PointXYZIHIRBS &pt);
    void SetupSinCosCache();
    std::unordered_map<int, LaserCorrection> laser_corrections_kv_;
    float distance_resolution_ = 0;
    int num_lasers_ = 0;
    int packet_count_ = 0;
    float sine_table_[ROTATION_MAX_UNITS];
    float cosine_table_[ROTATION_MAX_UNITS];

private:
    void LoadCalibrationFile(const std::string &path);
};

class VLP32Parser : public LidarParser {
public:
    explicit VLP32Parser(const std::string &path);
    bool PacketToPoint(RawPacket &pkt, pcl::PointCloud<PointXYZIHIRBS> &pc);
};


#endif//PACKET2PCL_RVIZ_DEMO_TRANSFORM_H_
