#include "merkle/hash.h"
// #include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
// #include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>

Hash::Hash(std::string msg)
{
    _hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    _digest.resize(_hash.DigestSize());
}

void Hash::update(std::string msg)
{
    _hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    _digest.resize(_hash.DigestSize());
}

std::string Hash::toString()
{
    std::string output;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));
    CryptoPP::StringSource(_digest, true, new CryptoPP::Redirector(encoder));
    return output;
}

bool Hash::verify()
{
    bool verified = _hash.Verify((const CryptoPP::byte*)_digest.data());
    return verified;
}

std::string Hash::final()
{
    _hash.Final((CryptoPP::byte*)&_digest[0]);
    return _digest;
}
