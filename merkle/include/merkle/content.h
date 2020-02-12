#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

#include <cryptopp/sha.h>
#include <string>
#include <vector>

class Content {
public:
    Content() {}
    Content(std::string);
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> calculateHash();
    bool equals(Content);
    bool verify();
    void print();

private:
    std::string _content;
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> _digest;
    CryptoPP::SHA256 _hash;
};

#endif
