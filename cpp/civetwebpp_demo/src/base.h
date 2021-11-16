/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:13
*/
#ifndef CIVETWEBPP_DEMO_BASE_H
#define CIVETWEBPP_DEMO_BASE_H
#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>
#include <memory>
#include <nlohmann/json.hpp>
#include <utility>
#include <unistd.h>
#include "CivetServer.h"


namespace trunk {
namespace infra {
namespace http {
class HttpBase : public CivetHandler {
public:
    HttpBase();
};

class WebSocketBase : public CivetWebSocketHandler {
public:
    thread_local static std::stringstream m_data;
    thread_local static unsigned char m_current_opcode;
    using Json = nlohmann::json;
    using Connection = struct mg_connection;

    explicit WebSocketBase(std::string name);

    /**
     * @brief Callback method for when the client intends to establish a websocket
     * connection, before websocket handshake.
     *
     * @param server the calling server
     * @param conn the connection information
     * @returns true to keep socket open, false to close it
     */
    bool handleConnection(CivetServer *server, const Connection *conn) override;

    /**
     * @brief Callback method for when websocket handshake is successfully
     * completed, and connection is ready for data exchange.
     *
     * @param server the calling server
     * @param conn the connection information
     */
    void handleReadyState(CivetServer *server, Connection *conn) override;

    /**
     * @brief Callback method for when a data frame has been received from the
     * client.
     *
     * @details In the websocket protocol, data is transmitted using a sequence of
     * frames, and each frame received invokes this callback method. Since the
     * type of opcode (text, binary, etc) is given in the first frame, this method
     * stores the opcode in a thread_local variable named current_opcode_. And
     * data from each frame is accumulated to data_ until the final fragment is
     * detected. See websocket RFC at http://tools.ietf.org/html/rfc6455, section
     * 5.4 for more protocol and fragmentation details.
     *
     * @param server the calling server
     * @param conn the connection information
     * @param bits first byte of the websocket frame, see websocket RFC at
     *             http://tools.ietf.org/html/rfc6455, section 5.2
     * @param data payload, with mask (if any) already applied.
     * @param data_len length of data
     * @returns true to keep socket open, false to close it
     */
    bool handleData(CivetServer *server, Connection *conn, int bits, char *data,
                    size_t data_len) override;

    /**
     * @brief Callback method for when the connection is closed.
     *
     * @param server the calling server
     * @param conn the connection information
     */
    void handleClose(CivetServer *server, const Connection *conn) override;

    /**
     * @brief Sends the provided data to all the connected clients.
     * @param data The message string to be sent.
     */
    bool BroadcastData(const std::string &data, bool skippable = false);

    /**
     * @brief Sends the provided data to a specific connected client.
     *
     * @param conn The connection to send to.
     * @param data The message string to be sent.
     * @param skippable whether the data is allowed to be skipped if some other is
     * being sent to this connection.
     */
    bool SendData(Connection *conn, const std::string &data,
                  bool skippable = false, int op_code = MG_WEBSOCKET_OPCODE_TEXT);

    bool SendBinaryData(Connection *conn, const std::string &data,
                        bool skippable = false);

private:
    const std::string m_name;

    // The mutex guarding the connection set. We are not using read
    // write lock, as the server is not expected to get many clients
    // (connections).
    // CAVEAT: Execution section while holding this global lock should be as
    // brief as possible.
    mutable std::mutex m_mutex;

    // The pool of all maintained connections. Each connection has a lock to
    // guard against simultaneous write.
    std::unordered_map<Connection*, std::shared_ptr<std::mutex>> m_user_pool;

};

}// namespace http
}// namespace infra
}// namespace trunk

#endif//CIVETWEBPP_DEMO_BASE_H
