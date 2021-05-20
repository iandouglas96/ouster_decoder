#include "decoder.h"

#include "ouster_ros/OSConfigSrv.h"

namespace ouster_decoder {

namespace sensor = ouster_ros::sensor;

Decoder::Decoder(const ros::NodeHandle& pnh) : pnh_(pnh), it_(pnh) {
  // Call service to retrieve sensor info, this must be done first
  ouster_ros::OSConfigSrv cfg{};
  auto client = pnh_.serviceClient<ouster_ros::OSConfigSrv>("os_config");
  client.waitForExistence();
  if (!client.call(cfg)) {
    throw std::runtime_error("Calling config service failed");
  }

  ROS_INFO("Parsing OSConfig");
  info_ = sensor::parse_metadata(cfg.response.metadata);
}

void Decoder::LidarPacketCb(const ouster_ros::PacketMsg& lidar_msg) {}

void Decoder::ImuPacketCb(const ouster_ros::PacketMsg& imu_msg) {}

}  // namespace ouster_decoder
