#include "server/server.h"
#include <iostream>

/*
 * `start()` launches the server and iterates through the `endpoint` objects,
 * serving their content at the specified path
 */
void Server::start(std::vector<endpoint> endpoints)
{
    std::cout << "\n";
    std::cout << "contents: \n" << std::endl;
    std::cout << "\n";
    std::cout << "serving at " << _host << ":" << _port << "/" << std::endl;

    for (endpoint e : endpoints) {
        _svr.Get(e.path.c_str(),
            [e](const httplib::Request& req, httplib::Response& res) {
                res.set_content(e.content, e.content_type.c_str());
            });
        std::cout << _host << ":" << _port << e.path << std::endl;
    }
    _svr.listen(_host.c_str(), _port);
}

void Server::stop() { _svr.stop(); }
