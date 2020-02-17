#ifndef __MERKLE_TREE_H_INCLUDED__
#define __MERKLE_TREE_H_INCLUDED__

class Content;
class Node;

#include "merkle/node.h"
#include <vector>

class MerkleTree {
public:
    MerkleTree(std::vector<Content>);

    std::vector<std::tuple<std::string, int>> getMerklePath(Content);

    std::string getMerkleRoot() { return _merkleRoot; }

    std::vector<Node*> getLeafs() { return _leafs; }
    Node* getRoot() { return _root; }

    void rebuild();
    void rebuildWithContent(std::vector<Content>);
    bool verify();
    bool verifyContent(Content);

private:
    void buildLeafs();
    void buildRoot(std::vector<Node*>);
    void build(std::vector<Content>);

    std::string _merkleRoot;
    Node* _root;
    std::vector<Node*> _leafs;
};

#endif
