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
    Node(Node*, Node*, std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>, MerkleTree*);
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> getHash() {
	return _hash;
    }
    Content getContent() { return _content; }
    void setParent(Node* n) { _parent = n; }

private:
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>  verify();
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>  calculateHash();

    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> _hash;
    Content _content;
    MerkleTree* _tree;
    bool _leaf;
    bool _dup;
    Node* _parent;
    Node* _left;
    Node* _right;
};

#endif
