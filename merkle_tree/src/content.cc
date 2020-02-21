// internal
#include "merkle/content.h"
#include "merkle/hash.h"

/*
 * `calculateHash()` wraps the `Hash` by passing the path to the `file()`
 * function and storing the resulting output. Storing the result allows the
 * class to prevent the function from being called multiple times.
 */
std::string Content::calculateHash()
{
    if (!_digest.empty()) {
        return _digest;
    }

    _digest = _hash.file(_path);
    return _digest;
}
