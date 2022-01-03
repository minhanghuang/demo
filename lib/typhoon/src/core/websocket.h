/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:22
 */
#ifndef TYPHOON_CORE_WEBSOCKET_H_
#define TYPHOON_CORE_WEBSOCKET_H_
#include <sstream>
#include <utility>
#include <iostream>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "CivetServer.h"

namespace trunk {
namespace typhoon {
namespace websocket {

typedef mg_connection Connection;

class WebSocketHandler : public CivetWebSocketHandler {
 public:
  thread_local static std::stringstream ws_data;
  thread_local static unsigned char current_opcode;
  explicit WebSocketHandler(std::string name);
  bool handleConnection(CivetServer *server, const Connection *conn) override;
  void handleReadyState(CivetServer *server, Connection *conn) override;
  bool handleData(CivetServer *server,
                  Connection *conn,
                  int bits,
                  char *data,
                  size_t data_len) override;

  void handleClose(CivetServer *server, const Connection *conn) override;

  /**
   * @brief: 广播
   * */
  bool BroadcastData(const std::string& data, bool skippable = false);
  /**
   * @brief: 单播
   * */
  bool SendData(Connection *conn,
                const std::string &data,
                bool skippable = false,
                int op_code = MG_WEBSOCKET_OPCODE_TEXT);
  bool SendBinaryData(Connection* conn,
                      const std::string& data,
                      bool skippable = false);

 private:
  std::string name_;
  mutable std::mutex mutex_;
  std::unordered_map<Connection *, std::shared_ptr<std::mutex>> user_pool_;

};

}  // namespace websocket
}  // namespace typhoon
}  // namespace trunk

#endif  // TYPHOON_CORE_WEBSOCKET_H_
