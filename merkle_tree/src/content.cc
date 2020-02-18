#include "merkle/content.h"
#include "merkle/hash.h"

std::string Content::calculateHash()
{
    if (!_digest.empty()) {
        return _digest;
    }

    _digest = _hash.file(_path);
    return _digest;
}
