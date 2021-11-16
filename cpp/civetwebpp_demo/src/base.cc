/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:13
*/
#include "base.h"

#include <utility>

namespace trunk {
namespace infra {
namespace http {
HttpBase::HttpBase() = default;

WebSocketBase::WebSocketBase(std::string name) : m_name(std::move(name)) {}

bool WebSocketBase::handleConnection(CivetServer *server, const WebSocketBase::Connection *conn) {
    std::cout << m_name
              <<  ": Connection ... " << std::endl;
    return true;
}

void WebSocketBase::handleReadyState(CivetServer *server, Connection *conn) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_user_pool.emplace(conn, std::make_shared<std::mutex>());
    }
    std::cout << m_name
              << ": Accepted connection. Total connections: " << m_user_pool.size() << std::endl;
}

thread_local unsigned char WebSocketBase::m_current_opcode = 0x00;
thread_local std::stringstream WebSocketBase::m_data;

bool WebSocketBase::handleData(CivetServer* server, Connection* conn,
                               int bits, char *data, size_t data_len) {
    std::cout << m_name << ": recv data " << std::endl;
    // Ignore connection close request.
    if ((bits & 0x0F) == MG_WEBSOCKET_OPCODE_CONNECTION_CLOSE) {
        return false;
    }
    m_data.write(data, data_len);
    if (m_current_opcode == 0x00) {
        m_current_opcode = bits & 0x7f;
    }

    // The FIN bit (the left most significant bit) is used to indicates
    // the final fragment in a message. Note, the first fragment MAY
    // also be the final fragment.
    bool is_final_fragment = bits & 0x80;
    if (is_final_fragment) {
        switch (m_current_opcode) {
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
        m_current_opcode = 0x00;
        m_data.clear();
        m_data.str(std::string());
    }

    return true;
}

void WebSocketBase::handleClose(CivetServer* server,
                                const Connection* conn) {
    // Remove from the store of currently open connections. Copy the mutex out
    // so that it won't be reclaimed during map.erase().
    auto *connection = const_cast<Connection*>(conn);

    std::shared_ptr<std::mutex> user_lock;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        user_lock = m_user_pool[connection];
    }

    {
        // Make sure there's no data being sent via the connection
        std::unique_lock<std::mutex> lock_connection(*user_lock);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_user_pool.erase(connection);
    }

    std::cout << m_name
              << ": Connection closed. Total connections: " << m_user_pool.size() << std::endl;
}

bool WebSocketBase::BroadcastData(const std::string &data, bool skippable) {
    std::vector<Connection*> users_to_send;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_user_pool.empty()) {
            return true;
        } else {
            for (auto& user : m_user_pool) {
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

bool WebSocketBase::SendData(Connection *conn, const std::string &data,
                             bool skippable, int op_code) {
    std::shared_ptr<std::mutex> connection_lock;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        // Copy the lock so that it still exists if the connection is closed after
        // this block.
        connection_lock = m_user_pool[conn];
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
        std::unique_lock<std::mutex> lock(m_mutex);
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
        std::cout << m_name << ": Failed to send data via websocket connection. Reason";
        if (ret == 0) {
            std::cout << "Connection closed";
        } else if (ret < 0) {
            std::cout << "Send error: " << std::strerror(errno);
        } else {
            std::cout << "Bytes to send: expected " << data.size() << ", actual: " << ret;
        }
        return false;
    }

    return true;
}

bool WebSocketBase::SendBinaryData(Connection *conn, const std::string &data,
                                   bool skippable) {
    return SendData(conn, data, skippable, MG_WEBSOCKET_OPCODE_BINARY);
}


}// namespace http
}    // namespace infra
}// namespace trunk
