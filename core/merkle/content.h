#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

#include <vector>

class Content {
public:
    std::vector<unsigned char> calculateHash();
    bool equals(Content);
    bool verify();
};

#endif
