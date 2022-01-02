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

  class RequestHandler : public CivetHandler {
  public:
      RequestHandler();
      void Response(struct mg_connection *conn,
                    const nlohmann::json& data,
                    int32_t status_code);

};


} // namespace trunk
} // namespace typhoon
} // namespace web


#endif//TYPHOON_CORE_WEB_H_
