#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

// internal
#include "server/endpoint.h"

// system
#include <string>

// external
#include <httplib.h>

/*
 * An `endpoint` ensapsulates the details necessary to serve the content
 * correctly at the specified path
 */
struct endpoint {
    std::string path;
    std::string content;
    std::string content_type;
};
typedef struct endpoint endpoint;

/*
 * The `Server` contains the functionality to serve the verfied content on the
 * web
 */
class Server {
public:
    Server(std::string host, int port)
        : _host(host)
        , _port(port)
    {
    }
    ~Server() {
	stop();
    }

    void start(std::vector<Endpoint<std::string>>);
    void stop();

private:
    std::string _host = "localhost";
    int _port = 3000;
    httplib::Server _svr;
};

#endif
