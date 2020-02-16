#include "merkle/content.h"
#include "merkle/hash.h"

Content::Content(std::string msg)
{
    _msg = msg;
    _hash = Hash(msg);
}

std::string Content::calculateHash()
{
    _hash.final();
    return _hash.toString();
}

bool Content::verify() { return _hash.verify(); }
