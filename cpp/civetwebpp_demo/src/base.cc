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
    std::cout << "--- handleConnection" << std::endl;
    return true;
}

void WebSocketBase::handleReadyState(CivetServer *server, Connection *conn) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_connections.emplace(conn, std::make_shared<std::mutex>());
    }
    std::cout << m_name
              << ": Accepted connection. Total connections: " << m_connections.size();

    // Trigger registered new connection handlers.
    for (const auto& handler : m_connection_ready_handlers) {
        handler(conn);
    }
}

void WebSocketBase::handleClose(CivetServer *server,
                                const Connection *conn) {
    // Remove from the store of currently open connections. Copy the mutex out
    // so that it won't be reclaimed during map.erase().
    std::cout << "--- handleClose" << std::endl;
    auto *connection = const_cast<Connection *>(conn);

    std::shared_ptr<std::mutex> connection_lock;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        connection_lock = m_connections[connection];
    }

    {
        // Make sure there's no data being sent via the connection
        std::unique_lock<std::mutex> lock_connection(*connection_lock);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_connections.erase(connection);
    }

    std::cout << m_name
              << ": Connection closed. Total connections: " << m_connections.size();
}

bool WebSocketBase::BroadcastData(const std::string &data, bool skippable) {
    std::vector<Connection *> connections_to_send;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_connections.empty()) {
            return true;
        }
        for (auto &kv : m_connections) {
            Connection *conn = kv.first;
            connections_to_send.push_back(conn);
        }
    }

    bool all_success = true;
    for (Connection *conn : connections_to_send) {
        if (!SendData(conn, data, skippable)) {
            all_success = false;
        }
    }

    return all_success;
}

bool WebSocketBase::SendBinaryData(Connection *conn, const std::string &data,
                                   bool skippable) {
    return SendData(conn, data, skippable, MG_WEBSOCKET_OPCODE_BINARY);
}

bool WebSocketBase::SendData(Connection *conn, const std::string &data,
                             bool skippable, int op_code) {
    std::shared_ptr<std::mutex> connection_lock;
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        // Copy the lock so that it still exists if the connection is closed after
        // this block.
        connection_lock = m_connections[conn];
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

bool WebSocketBase::handleData(CivetServer *server, Connection *conn,
                               int bits, char *data, size_t data_len) {

    return true;
}

bool WebSocketBase::handleJsonData(Connection *conn,
                                   const std::string &data) {
    Json json;
    try {
        json = Json::parse(data.begin(), data.end());
    } catch (const std::exception &e) {
        return false;
    }

    auto type = json["type"];
    m_message_handlers[type](json, conn);
    return true;
}

bool WebSocketBase::handleBinaryData(Connection *conn,
                                     const std::string &data) {
    auto type = "Binary";
    m_message_handlers[type](data, conn);
    return true;
}

void WebSocketBase::RegisterMessageHandler(const std::string &type, WebSocketBase::MessageHandler handler) {
    m_message_handlers[type] = std::move(handler);
}

void WebSocketBase::RegisterConnectionReadyHandler(const WebSocketBase::ConnectionReadyHandler& handler) {
    m_connection_ready_handlers.emplace_back(handler);
}

}// namespace http
}    // namespace infra
}// namespace trunk
