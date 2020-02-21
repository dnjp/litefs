#include "server/server.h"
#include <iostream>

/*
 * `start()` launches the server and iterates through the `endpoint` objects,
 * serving their content at the specified path
 */
void Server::start(std::vector<Endpoint<std::string>> endpoints)
{
    std::cout << "serving contents at " << _host << ":" << _port << "/" << std::endl;

    for (Endpoint e : endpoints) {
        _svr.Get(e.path.c_str(),
            [e](const httplib::Request& req, httplib::Response& res) {
                res.set_content(e.content, e.type.c_str());
            });
        std::cout << _host << ":" << _port << e.path << std::endl;
    }
    _svr.listen(_host.c_str(), _port);
}

void Server::stop() { _svr.stop(); }
