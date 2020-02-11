#include "merkle/content.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

Content::Content(std::string msg) // this can be replaced with a file
{
    _content = msg;
    // _hash.Update((const CryptoPP::byte*)_content.data(), _content.size());
    // _digest.resize(_hash.DigestSize());
    CryptoPP::StringSource s(_content, true,
        new CryptoPP::HashFilter(_hash,
            new CryptoPP::ArraySink(
                _digest.data(), CryptoPP::SHA256::DIGESTSIZE)));
    
}

void Content::print()
{
    // CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    // CryptoPP::StringSource(_digest, true, new CryptoPP::Redirector(encoder));
    for (auto& it : _digest) {
	std::cout << std::hex << (int)it;	
    }
    std::cout << std::endl;
}

std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> Content::calculateHash()
{
    // _hash.Final((CryptoPP::byte*)&_digest[0]);
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
