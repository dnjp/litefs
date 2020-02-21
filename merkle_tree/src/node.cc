// internal
#include "merkle/node.h"

// system
#include <iostream>

/*
 * `calculateHash()` hashes the combined hashes of its sibling nodes and stores
 * it when it is not a leaf node, otherwise it returns the hash of its content.
 */
std::string Node::calculateHash()
{
    if (_leaf) {
        return content.calculateHash();
    }

    std::string lHash = left->hash;
    std::string rHash = right->hash;
    std::string cHash = lHash + rHash;

    Hash h = Hash(cHash);
    h.final();
    _digest = h.calculate();
    return _digest;
}

/*
 * `verify()` verifies its sibling nodes and returns the hash of their combined
 * hashes.
 */
std::string Node::verify()
{
    if (_leaf) {
        return content.calculateHash();
    }
    std::string lHash = left->verify();
    std::string rHash = right->verify();

    // add rightBytes to leftBytes
    std::string cHash = lHash + rHash;

    // add the result to the hash
    Hash hash = Hash(cHash);
    hash.final();
    return hash.calculate();
}
