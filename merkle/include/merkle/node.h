#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class MerkleTree;
class Content;

#include "merkle/content.h"
#include "merkle/tree.h"
#include "merkle/hash.h"

class Node {
public:
    Node(Hash, Content, bool, MerkleTree*);
    Node(Hash, Content, bool, bool, MerkleTree*);  
    Node(Node*, Node*, Hash, MerkleTree*);

    std::string verify();
    std::string calculateHash();

    Node* parent;
    Hash hash;
    Content content;
    Node* left;
    Node* right;

private:
    MerkleTree* _tree;
    bool _leaf;
    bool _dup;
    std::string _digest;

};

#endif
