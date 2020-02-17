#include "merkle/hash.h"
#include <iostream>

// CryptoPP
#include <cryptopp/channels.h>
#include <cryptopp/crc.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

Hash::Hash(std::string path)
{
    _hash.Update((const CryptoPP::byte*)path.data(), path.size());
    _digest.resize(_hash.DigestSize());
}

std::string Hash::calculate()
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

std::string Hash::file(std::string path)
{
    std::string crcOutput;
    CryptoPP::CRC32 crc;

    // validate integrity of file
    CryptoPP::HashFilter f1(
        crc, new CryptoPP::HexEncoder(new CryptoPP::StringSink(crcOutput)));
    // hash crc32 output
    CryptoPP::HashFilter f2(
        _hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(_digest)));

    CryptoPP::ChannelSwitch cs;
    // attach filters
    cs.AddDefaultRoute(f1);
    cs.AddDefaultRoute(f2);

    // run file through pipeline
    CryptoPP::FileSource(
        path.c_str(), true /*pumpAll*/, new CryptoPP::Redirector(cs));
    return _digest;
}
