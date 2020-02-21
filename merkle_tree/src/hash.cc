#include "merkle/hash.h"
#include <iostream>

// external
#include <cryptopp/channels.h>
#include <cryptopp/crc.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

/*
 * This constructor takes a string message and creates a CryptoPP::Hash object
 * which can be written to. CryptoPP::SHA256::Update is called internally which
 * updates the hash with the content of the message. This allows for a chained
 * style of interaction, calling `final()` on the hash when finished writing and
 * `calculate()` to return the string representation of the hash.
 */
Hash::Hash(std::string msg)
{
    _hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    _digest.resize(_hash.DigestSize());
}

/*
 * `final()` must be called on a CryptoPP::Hash object to generate the SHA256
 * hash representation of the data. Here that output, commonly called a
 * "digest", is captured in the private `_digest` varialbe.
 */
void Hash::final() { _hash.Final((CryptoPP::byte*)&_digest[0]); }

/*
 * `calculate()` runs the `_digest` through a pipeline which transforms it into
 * a human readable form.
 */
std::string Hash::calculate()
{
    std::string output;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));
    CryptoPP::StringSource(_digest, true, new CryptoPP::Redirector(encoder));
    return output;
}

/*
 * `verify()` is used on a finalized hash to verify that its contents haven't
 * been tampered with.
 */
bool Hash::verify()
{
    bool verified = _hash.Verify((const CryptoPP::byte*)_digest.data());
    return verified;
}

/*
 * `file()` provides a more convenient construction as opposed to the construct,
 * final, calculate method. It takes a path to the file as input, calculates the
 * hash, finalizes it, and returns the human readable form of the hash.
 */
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
