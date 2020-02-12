#include "merkle/content.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

Content::Content(std::string msg) // this can be replaced with a file
{
    _content = msg;
    CryptoPP::StringSource s(_content, true,
        new CryptoPP::HashFilter(_hash,
            new CryptoPP::ArraySink(
                _digest.data(), CryptoPP::SHA256::DIGESTSIZE)));
    
}

void Content::print()
{
    for (auto& it : _digest) {
	std::cout << std::hex << (int)it;	
    }
    std::cout << std::endl;
}

std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> Content::calculateHash()
{
    return _digest;
}

bool Content::equals(Content c) { return true; }

bool Content::verify()
{
    CryptoPP::SHA256 hash;
    hash.Update((const CryptoPP::byte*)_content.data(), _content.size());
    bool verified = hash.Verify((const CryptoPP::byte*)_digest.data());
    return verified;
}
