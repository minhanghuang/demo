/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:22
*/
#include "websocket.h"


namespace trunk {
namespace typhoon {
namespace websocket {

thread_local unsigned char WebSocketHandler::current_opcode = 0x00;
thread_local std::stringstream WebSocketHandler::ws_data;

WebSocketHandler::WebSocketHandler(std::string name) : name_(std::move(name)) {}

bool WebSocketHandler::handleConnection(CivetServer *server,
                                        const Connection *conn) {
  std::cout << name_ <<  ": Connection ... " << std::endl;
  return true;
}

void WebSocketHandler::handleReadyState(CivetServer *server, Connection *conn) {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    user_pool_.emplace(conn, std::make_shared<std::mutex>());
  }
  std::cout << name_
            << ": Accepted connection. Total connections: "
            << user_pool_.size() << std::endl;
}

bool WebSocketHandler::handleData(CivetServer *server,
                                  Connection *conn,
                                  int bits,
                                  char *data,
                                  size_t data_len) {
  std::cout << name_ << ": recv data " << std::endl;
  if (MG_WEBSOCKET_OPCODE_CONNECTION_CLOSE == (bits & 0x0F)) {
    return false;
  }
  ws_data.write(data, data_len);
  if (current_opcode == 0x00) {
    current_opcode = bits & 0x7f;
  }
  bool is_final_fragment = bits & 0x80;
  if (is_final_fragment) {
    switch (current_opcode) {
      case MG_WEBSOCKET_OPCODE_TEXT:
        std::cout << "MG_WEBSOCKET_OPCODE_TEXT" << std::endl;
        break;
      case MG_WEBSOCKET_OPCODE_BINARY:
        std::cout << "MG_WEBSOCKET_OPCODE_BINARY" << std::endl;
        break;
      default:
        std::cout << "default" << std::endl;
        break;
    }

    // reset opcode and data
    current_opcode = 0x00;
    ws_data.clear();
    ws_data.str(std::string());
  }

  return true;
}

void WebSocketHandler::handleClose(CivetServer *server,
                                   const Connection *conn) {
  auto* connection = const_cast<Connection*>(conn);
  std::shared_ptr<std::mutex> user_lock;
  {
    std::unique_lock<std::mutex> lock(mutex_);
    user_lock = user_pool_[connection];
  }

  {
    // Make sure there's no data being sent via the connection
    std::unique_lock<std::mutex> lock_connection(*user_lock);
    std::unique_lock<std::mutex> lock(mutex_);
    user_pool_.erase(connection);
  }

  std::cout << name_
            << ": Connection closed. Total connections: "
            << user_pool_.size() << std::endl;
}

bool WebSocketHandler::BroadcastData(const std::string& data, bool skippable) {
  std::vector<Connection*> users_to_send;
  {
    std::unique_lock<std::mutex> lock(mutex_);
    if (user_pool_.empty()) {
      return true;
    } else {
      for (auto& user : user_pool_) {
        users_to_send.push_back(user.first);
      }
    }
  }

  bool all_success = true;
  for (Connection* conn : users_to_send) {
    if (!SendData(conn, data, skippable)) {
      all_success = false;
    }
  }

  return all_success;
}

bool WebSocketHandler::SendData(Connection *conn,
                                const std::string &data,
                                bool skippable,
                                int op_code) {
  std::shared_ptr<std::mutex> connection_lock;
  {
    std::unique_lock<std::mutex> lock(mutex_);
    // Copy the lock so that it still exists if the connection is closed after
    // this block.
    connection_lock = user_pool_[conn];
  }

  // Lock the connection while sending.
  if (!connection_lock->try_lock()) {
    // Skip sending data if:
    // 1. Data is skippable according to sender and there's higher priority data
    // being sent.
    // 2. The connection has been closed.
    if (skippable) {
      std::cout << "Skip sending a droppable message!";
      return false;
    }
    // Block to acquire the lock.
    connection_lock->lock();
    std::unique_lock<std::mutex> lock(mutex_);
  }

  // Note that while we are holding the connection lock, the connection won't be
  // closed and removed.
  int ret = mg_websocket_write(conn, op_code, data.c_str(), data.size());
  connection_lock->unlock();

  if (ret != static_cast<int>(data.size())) {
    // When data is empty, the header length (2) is returned.
    if (data.empty() && ret == 2) {
      return true;
    }

    // Determine error message based on return value.
    std::cout << name_
              << ": Failed to send data via websocket connection. Reason";
    if (ret == 0) {
      std::cout << "Connection closed";
    } else if (ret < 0) {
      std::cout << "Send error: " << errno << std::endl;
    } else {
      std::cout << "Bytes to send: expected "
                << data.size()
                << ", actual: " << ret;
    }
    return false;
  }

  return true;
}

bool WebSocketHandler::SendBinaryData(Connection* conn,
                    const std::string& data,
                    bool skippable) {
  return SendData(conn, data, skippable, MG_WEBSOCKET_OPCODE_BINARY);
}


} // namespace websocket
} // namespace typhoon
} // namespace trunk
