#ifndef __HASH_H_INCLUDED__
#define __HASH_H_INCLUDED__

#include <cryptopp/sha.h>

class Hash {
public:
    Hash() {}
    Hash(std::string);
    bool verify();
    void final();
    std::string calculate();
    std::string file(std::string path);

private:
    CryptoPP::SHA256 _hash;
    std::string _digest;
};

#endif
