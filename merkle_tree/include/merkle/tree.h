#ifndef __MERKLE_TREE_H_INCLUDED__
#define __MERKLE_TREE_H_INCLUDED__

class Content;
class Node;

#include "merkle/node.h"
#include <vector>
#include <memory>

class MerkleTree {
public:
    MerkleTree(std::vector<Content>);

    std::string getMerkleRoot() { return _merkleRoot; }
    std::vector<std::tuple<std::string, int>> getMerklePath(Content);
    bool verify();
    bool verifyContent(Content);
    int getSize() { return _leafs.size(); }

private:
    void buildLeafs();
    void buildRoot(std::vector<Node*>);    
    void build(std::vector<Content>);

    // data handles for recursive traversal 
    std::vector<Node*> getNodeDataHandles();

    std::string _merkleRoot;

    // Data Handle (non-owned)
    Node* _root;

    // Data Handle (owned)
    std::vector<std::unique_ptr<Node>> _leafs;
};

#endif
