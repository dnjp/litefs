#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <string>
#include <httplib.h>

struct endpoint {
    std::string path;
    std::string content;
    std::string content_type;        
};
typedef struct endpoint endpoint;

class Server {
public:
    Server(std::string host, int port)
        : _host(host)
        , _port(port)
    {
    }

    void start(std::vector<endpoint>);
    void stop();

private:
    std::string _host = "localhost";
    int _port = 3000;
    httplib::Server _svr;
};

#endif
