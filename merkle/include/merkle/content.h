#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

#include "merkle/hash.h"
#include <string>
#include <vector>

class Content {
public:
    Content() {}
    Content(std::string);
    std::string calculateHash();
    std::string getMessage() { return _msg; }
    bool equals(Content);
    bool verify();

    bool operator==(const Content c) { return _msg == c._msg; }
    bool operator!=(const Content c) { return _msg != c._msg; }

private:
    std::string _msg;
    Hash _hash = Hash();
};

#endif
