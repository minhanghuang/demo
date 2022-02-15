#include "transform.h"

LidarParser::LidarParser(const std::string& path) {
    LoadCalibrationFile(path);
    SetupSinCosCache();
}

void LidarParser::LoadCalibrationFile(const std::string& path) {
    std::cout << "path:" << path << std::endl;
    YAML::Node yaml_node = YAML::LoadFile(path);
    num_lasers_ = yaml_node["num_lasers"].as<int>();
    distance_resolution_ = yaml_node["distance_resolution"].as<float>();
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
    }  // for

    double next_angle = -std::numeric_limits<double>::infinity();
    for (int ring = 0; ring < num_lasers_; ++ring) {
        // find minimum remaining vertical offset correction
        double min_seen = std::numeric_limits<double>::infinity();
        int next_index = num_lasers_;
        for (int j = 0; j < num_lasers_; ++j) {
            double angle = laser_corrections_kv_[j].vert_correction;
            if (next_angle < angle && angle < min_seen) {
                min_seen = angle;
                next_index = j;
            }
        }

        if (next_index < num_lasers_) {  // anything found in this ring?
            // store this ring number with its corresponding laser number
            laser_corrections_kv_[next_index].laser_ring = ring;
            next_angle = min_seen;
        }
    }
}

void LidarParser::ConvertCoordinate(float radius, int azimuth, const LaserCorrection& correction,
                                    PointXYZIHIRBS& pt) {
    radius += correction.dist_correction;
    // 三角函数
    float cos_w = correction.cos_vert_correction;
    float sin_w = correction.sin_vert_correction;
    float cos_a =
            cosine_table_[azimuth] * correction.cos_rot_correction + sine_table_[azimuth] * correction.sin_rot_correction;
    float sin_a =
            sine_table_[azimuth] * correction.cos_rot_correction - cosine_table_[azimuth] * correction.sin_rot_correction;

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
            ? ((x - 2.4) / (25.04 - 2.4) - 1) * (correction.dist_correction - correction.dist_correction_x)
            : 0;
    float radius_ajust_by_y =
            correction.two_pt_correction_available
            ? ((y - 1.93) / (25.04 - 1.93) - 1) * (correction.dist_correction - correction.dist_correction_y)
            : 0;
    float x_coord = ((radius + radius_ajust_by_x) * cos_w - xy_adjust) * sin_a - x_adjust;
    float y_coord = ((radius + radius_ajust_by_y) * cos_w - xy_adjust) * cos_a + y_adjust;
    float z_coord = (radius + radius_ajust_by_y) * sin_w + z_adjust;
    // 坐标系旋转
    pt.x = y_coord;
    pt.y = -x_coord;
    pt.z = z_coord;
}

void LidarParser::CalcIntensity(float radius, int reflectivity, const LaserCorrection& correction,
                                PointXYZIHIRBS& pt) {
    float focal_offset = 256 * std::pow(1 - correction.focal_distance / 13100, 2);
    float focal_slope = correction.focal_slope;
    float intensity = reflectivity + focal_slope * std::abs(focal_offset - 256 * std::pow(1 - radius / 65535, 2));
    pt.intensity = std::max(static_cast<float>(correction.min_intensity),
                            std::min(intensity, static_cast<float>(correction.max_intensity)));
}

void LidarParser::SetupSinCosCache() {
    for (uint16_t rot_index = 0; rot_index < ROTATION_MAX_UNITS; ++rot_index) {
        float rotation = (ROTATION_RESOLUTION * rot_index) * M_PI / 180.0;
        cosine_table_[rot_index] = cosf(rotation);
        sine_table_[rot_index] = sinf(rotation);
    }
}



VLP32Parser::VLP32Parser(const std::string& path) : LidarParser(path) {}

bool VLP32Parser::PacketToPoint(RawPacket& pkt, pcl::PointCloud<PointXYZIHIRBS>& pc) {
    for (int block = 0; block < 12; block++) {
        int azimuth = pkt.blocks[block].azimuth;
        for (int channel = 0; channel < 32; channel++) {
            LaserCorrection& correction = laser_corrections_kv_[channel];
            float radius = pkt.blocks[block].data[channel].radius * distance_resolution_;
            PointXYZIHIRBS p;
            ConvertCoordinate(radius, azimuth, correction, p);   // xyz
            pc.points.emplace_back(p);
        }
    }  // for
    if (packet_count_ >= 150) {
        packet_count_ = 0;
        return true;
    }
    packet_count_++;
    return false;
}

