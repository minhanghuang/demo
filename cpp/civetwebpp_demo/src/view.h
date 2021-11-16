/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:13
*/
#ifndef CIVETWEBPP_DEMO_VIEW_H
#define CIVETWEBPP_DEMO_VIEW_H
#include "base.h"
#include <utility>

class OkView : public trunk::infra::http::HttpBase {
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn) override;
    bool handlePost(CivetServer *server, struct mg_connection *conn) override;
    bool handlePut(CivetServer *server, struct mg_connection *conn) override;
};

class SimpleWebsocket : public trunk::infra::http::WebSocketBase {
public:
    explicit SimpleWebsocket(std::string name);
};

#endif//CIVETWEBPP_DEMO_VIEW_H
