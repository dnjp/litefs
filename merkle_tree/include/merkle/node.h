#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class MerkleTree;
class Content;

#include "merkle/content.h"
#include "merkle/hash.h"
#include "merkle/tree.h"

class Node {
public:
    Node(std::string, Content, bool, MerkleTree*);
    Node(std::string, Content, bool, bool, MerkleTree*);
    Node(Node*, Node*, std::string, MerkleTree*);

    std::string calculateHash();
    std::string verify();

    // Data Handles (non-owning)
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    MerkleTree* tree = nullptr;
    
    Content content = Content();
    std::string hash;

private:
    bool _leaf = false;
    bool _dup;
    std::string _digest;
};

#endif
