#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class MerkleTree;
class Content;

#include "merkle/content.h"
#include "merkle/tree.h"
#include <vector>

class Node {
public:
    MerkleTree* tree;
    Node* parent;
    Node* left;
    Node* right;
    std::vector<unsigned char> hash;
    Content content;

private:
    std::vector<unsigned char> verify();
    std::vector<unsigned char> calculateHash();

    bool _leaf;
    bool _dup;
};

#endif
