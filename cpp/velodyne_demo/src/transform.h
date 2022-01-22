#ifndef VELODYNE_DEMO_TRANSFORM_H_
#define VELODYNE_DEMO_TRANSFORM_H_

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

class VelodyneParser {
public:
  VelodyneParser();

};

#endif // VELODYNE_DEMO_TRANSFORM_H_
