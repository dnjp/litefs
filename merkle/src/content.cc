#include "merkle/content.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

Content::Content(std::string msg)
{
    _content = msg;
    _hash.Update((const CryptoPP::byte*)_content.data(), _content.size());
    _digest.resize(_hash.DigestSize());
    _hash.Final((CryptoPP::byte*)&_digest[0]);
}

void Content::print()
{
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    CryptoPP::StringSource(_digest, true, new CryptoPP::Redirector(encoder));
}

// std::vector<unsigned char> Content::calculateHash() {

// }

bool Content::equals(Content c)
{
    return true;
}

bool Content::verify()
{
    CryptoPP::SHA256 hash;
    hash.Update((const CryptoPP::byte*)_content.data(), _content.size());
    bool verified = hash.Verify((const CryptoPP::byte*)_digest.data());
    return verified;
}
