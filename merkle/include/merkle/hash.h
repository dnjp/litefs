#ifndef __HASH_H_INCLUDED__
#define __HASH_H_INCLUDED__

#include <cryptopp/sha.h>

class Hash {
public:
    Hash() {}
    Hash(std::string);
    void update(std::string);
    bool verify();
    std::string final();
    std::string toString();

private:
    CryptoPP::SHA256 _hash;
    std::string _digest;
};

#endif
