#ifndef __ENDPOINT_H_INCLUDED__
#define __ENDPOINT_H_INCLUDED__

// system
#include <string>

/*
 * An `endpoint` ensapsulates the details necessary to serve the content
 * correctly at the specified path where the content can be any type
 */
template<class T> class Endpoint {
public:
    Endpoint(std::string p, std::string type, T c) : path(p), content(c) {}
    std::string path;
    std::string type;    
    T content;
};

#endif
