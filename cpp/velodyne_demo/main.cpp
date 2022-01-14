#include <iostream>
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

inline uint16_t bytes_to_uint16(const uint8_t* bytes) { return (uint16_t)(bytes[0] + (bytes[1] << 8)); }

inline uint32_t bytes_to_uint32(const uint8_t* bytes) {
    return (uint32_t)(bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24));
}

inline double from_degrees(double degrees) { return degrees * M_PI / 180.0; }

inline double to_degrees(double radians) { return radians * 180.0 / M_PI; }

inline float SQR(float val) { return val * val; }

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

struct PointXYZIT {
    PCL_ADD_POINT4D;
    uint8_t intensity;
    float angle;
    uint8_t ring;
    double timestamp;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

} EIGEN_ALIGN16;

const float HIT_NAN = std::numeric_limits<float>::max();
const float HIT_FREE = std::numeric_limits<float>::min();

struct PointXYZIRPYT {
    PCL_ADD_POINT4D

            PCL_ADD_INTENSITY;
    float roll;
    float pitch;
    float yaw;
    double time;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

/// 全量信息的点云（带height,range,ring)
struct PointXYZIHIRBS {
    PCL_ADD_POINT4D;
    float height;
    float range;
    uint8_t intensity;
    uint8_t intensity_vi;
    uint8_t ring;
    uint8_t type;
    inline PointXYZIHIRBS() {
        x = y = z = 0.0f;
        intensity = intensity_vi = ring = type = 0;
        height = range = 0.0f;
    }
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

typedef pcl::PointXYZ PointXYZ;
typedef pcl::PointCloud<PointXYZ> PointCloudXYZ;
typedef pcl::PointXYZI PointXYZI;
typedef pcl::PointCloud<PointXYZI> PointCloudXYZI;
typedef pcl::PointCloud<PointXYZI>::Ptr CloudPtr;
typedef pcl::PointCloud<PointXYZIT> PointCloudXYZIT;
typedef pcl::PointCloud<PointXYZIRPYT> PointCloudXYZIRPYT;
typedef pcl::PointCloud<PointXYZIHIRBS> PointCloudXYZIHIRBS;

/// 点云类型定义
/// 建图时将主要使用这个点云作为主要类型表示
typedef PointXYZIHIRBS PointType;
typedef pcl::PointCloud<PointType> PointCloudType;
typedef pcl::PointCloud<PointType>::Ptr PointCloudPtr;


POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIT,
(float, x, x)(float, y, y)(float, z, z)(std::uint8_t, intensity, intensity)(
float, angle, angle)(std::uint8_t, ring, ring)(double, timestamp, timestamp))

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIRPYT,
(float, x, x)(float, y, y)(float, z, z)(float, intensity, intensity)(
float, roll, roll)(float, pitch, pitch)(float, yaw, yaw)(double, time, time))

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIHIRBS,
(float, x, x)(float, y, y)(float, z, z)(std::uint8_t, intensity, intensity)(
float, height, height)(std::uint8_t, intensity_vi, intensity_vi)(
float, range, range)(std::uint8_t, ring, ring)(std::uint8_t, type, type))



int main(int argc, char **argv) {
    std::cout << "Hello, Velodyne!" << std::endl;

    ros::init(argc, argv, "velodyne_demo");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("/home/mapdev/data/test/A001/A1.bag", rosbag::bagmode::Read);

    for (const auto& m : rosbag::View(bag)) {
        if ("/vlp16_1/velodyne_packets" == m.getTopic()) {
            auto v16 = m.instantiate<velodyne_msgs::VelodyneScan>();
            if (v16 != nullptr) {
                std::cout << "---" << m.getTopic() << std::endl;
            }
        }
    }

    return 0;
}
