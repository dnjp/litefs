#ifndef __HASH_H_INCLUDED__
#define __HASH_H_INCLUDED__

// external
#include <cryptopp/sha.h>

/*
 * Hash wraps the [Crypto++](https://www.cryptopp.com/) library and provides
 * high level abstractions that are relevant to generating a SHA256 hash from
 * the contents of a file or a string.
 */
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
