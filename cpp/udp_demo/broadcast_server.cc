/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/27 17:41
 */
#include <asio.hpp>
#include <iostream>

struct Frame { // 367个元素
  float Stamp=0; // 0
  uint8_t RllCounter=0; // 1
  uint8_t egoLaneSeg=0;// 2
  uint8_t LeftLaneSeg=0;
  uint8_t RightLaneSeg=0;
  uint8_t RoadType=0; // 5
  uint8_t TotalLaneNum=0;
  uint8_t egoLaneNum=0;
  uint8_t TrafficSignType=0;
  float TrafficSignRange=200;
  float TrafficSignValue=80; // 10
  float egoLaneMaxSpd=80;
  float LeftLaneMaxSpd=80;
  float RightLaneMaxSpd=80;
  float egoLaneWidth=3.75;
  float LeftLaneWidth=3.75; // 15
  float RightLaneWidth=3.75;
  float Offset2Turn=0;
  uint8_t NaviTurnFlag=0;
  uint8_t egoLaneLeft_st=0;
  float egoLaneLeft_start=0; // 20
  float egoLaneLeft_end=0;
  float egoLaneLeft_A0=0;
  float egoLaneLeft_A1=0;
  float egoLaneLeft_A2=0;
  float egoLaneLeft_A3=0; // 25
  uint8_t egoLaneRight_st=0;
  float egoLaneRight_start=0;
  float egoLaneRight_end=0;
  float egoLaneRight_A0=0;
  float egoLaneRight_A1=0; // 30
  float egoLaneRight_A2=0;
  float egoLaneRight_A3=0;
  uint8_t LeftLaneLeft_st=0;
  float LeftLaneLeft_start=0;
  float LeftLaneLeft_end=0; // 35
  float LeftLaneLeft_A0=0;
  float LeftLaneLeft_A1=0;
  float LeftLaneLeft_A2=0;
  float LeftLaneLeft_A3=0;
  uint8_t RightLaneRight_st=0; // 40
  float RightLaneRight_start=0;
  float RightLaneRight_end=0;
  float RightLaneRight_A0=0;
  float RightLaneRight_A1=0;
  float RightLaneRight_A2=0; // 45
  float RightLaneRight_A3=0;
  float PointHA[40]{}; // 47~86
  float PointXs[40]{}; // 87~126
  float PonitYs[40]{}; // 127~166
  float Slope_x[40]{}; // 167~206
  float Slope_y[40]{}; // 207~246
  float LaneCure[40]{}; // 247~286
  uint8_t LaneLeftType[40]{};
  uint8_t LaneRightType[40]{};
};

#define maxlength 1400


int main() {
  namespace ip = asio::ip;
  asio::io_service io_service;
  ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), 9005));

  ip::udp::endpoint sender_endpoint;
  while (true) {
    unsigned char recv_buf[maxlength];

    std::size_t length = socket.receive_from(asio::buffer(recv_buf, maxlength), sender_endpoint);
    auto* pp= (Frame *)recv_buf;
    std::cout << "length:" << length <<std::endl;
    std::cout << "LaneLeftType:" << pp->LaneLeftType <<std::endl;
  }

}
