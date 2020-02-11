#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class MerkleTree;
class Content;

#include "merkle/content.h"
#include "merkle/tree.h"

class Node {
public:
    Node(std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>, Content, bool, MerkleTree*);
    Node(std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>, Content, bool, bool, MerkleTree*);    
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> getHash() {
	return _hash;
    }
    Content getContent() { return _content; }

    Node* parent;
    Node* left;
    Node* right;

private:
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>  verify();
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>  calculateHash();

    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> _hash;
    Content _content;
    MerkleTree* _tree;
    bool _leaf;
    bool _dup;
};

#endif
