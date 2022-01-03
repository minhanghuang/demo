/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:22
 */
#ifndef TYPHOON_CORE_WEB_H_
#define TYPHOON_CORE_WEB_H_
#include <nlohmann/json.hpp>

#include "CivetServer.h"

namespace trunk {
namespace typhoon {
namespace web {

typedef mg_connection Connection;

class RequestHandler : public CivetHandler {
 public:
  typedef mg_request_info Info;
  RequestHandler();
  static nlohmann::json RequestData(Connection *conn);
  static const Info* RequestInfo(Connection *conn);
  static std::string RequestParam(Connection *conn, const std::string& key);
  static void Response(Connection *conn,
                       const nlohmann::json &data,
                       int32_t status_code);
};

}  // namespace web
}  // namespace typhoon
}  // namespace trunk

#endif  // TYPHOON_CORE_WEB_H_
