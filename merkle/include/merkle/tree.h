#ifndef __MERKLE_TREE_H_INCLUDED__
#define __MERKLE_TREE_H_INCLUDED__

class Content;
class Node;

#include "merkle/node.h"
#include <cryptopp/sha.h>
#include <vector>

class MerkleTree {
public:
    MerkleTree(std::vector<Content> content);

    std::vector<std::vector<unsigned char>> getMerklePath(Content);
    std::vector<unsigned char> getMerkleRoot() { return _merkleRoot; }
    std::vector<Node*> getLeafs() { return _leafs; }
    Node* getRoot() { return _root; }

    void rebuild();
    void rebuildWithContent(std::vector<Content>);
    bool verify();

private:
    void buildLeafs();
    void buildRoot();

    std::vector<unsigned char> _merkleRoot;
    Node* _root;
    std::vector<Node*> _leafs;
};

#endif
