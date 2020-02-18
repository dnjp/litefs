#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

#include "merkle/hash.h"
#include <string>
#include <vector>

class Content {
public:
    Content() {}
    Content(std::string path)
        : _path(path)
    {
    }
    std::string getPath() { return _path; }
    std::string calculateHash();

    bool operator==(const Content c) { return _path == c._path; }
    bool operator!=(const Content c) { return _path != c._path; }

private:
    std::string _path;
    Hash _hash = Hash();
    std::string _digest;
};

#endif
