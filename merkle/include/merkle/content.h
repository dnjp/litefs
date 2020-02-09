#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

#include <cryptopp/sha.h>
#include <string>
#include <vector>


class Content {
public:
    Content(std::string);
    // std::vector<unsigned char> calculateHash();
    bool equals(Content);
    bool verify();
    void print();

private:
    std::string _content;
    std::string _digest;
    CryptoPP::SHA256 _hash;
};

#endif
