#include "merkle/node.h"
#include <iostream>

Node::Node(std::string h, Content* c, bool isLeaf, MerkleTree* t)
{
    hash = h;
    content = c;
    _leaf = isLeaf;
    _tree = t;
}

Node::Node(std::string h, Content* c, bool isLeaf, bool dup, MerkleTree* t)
{
    hash = h;
    content = c;
    _leaf = isLeaf;
    _dup = dup;
    _tree = t;
}

Node::Node(Node* l, Node* r, std::string h, MerkleTree* t)
{
    left = l;
    right = r;
    hash = h;
    _tree = t;
}

std::string Node::verify()
{
    if (_leaf) {
        return content->calculateHash();
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

std::string Node::calculateHash()
{
    if (_leaf) {
        return content->calculateHash();
    }

    std::string lHash = left->hash;
    std::string rHash = right->hash;
    std::string cHash = lHash + rHash;

    Hash h = Hash(cHash);
    h.final();
    _digest = h.calculate();
    return _digest;
}
