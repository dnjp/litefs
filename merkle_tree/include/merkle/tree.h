#ifndef __MERKLE_TREE_H_INCLUDED__
#define __MERKLE_TREE_H_INCLUDED__

class Content;
class Node;

// internal
#include "merkle/node.h"

// system
#include <memory>
#include <vector>

/*
 * A MerkleTree is a hash tree constructed from the bottom up and is used to
 * cryptographically verify the contents for each node in the tree. Each leaf
 * node is labeled and contains the hashed contents of its block of data, a file
 * in this case. The non-leaf nodes contain a hash of its child nodes.
 * The root hash is made up of the hashes of all of its nodes which enables us
 * to ensure the contents have not changed by simply evaluating the merkle root.
 */
class MerkleTree {
public:
    MerkleTree(std::vector<Content>);

    std::string getMerkleRoot() { return _merkleRoot; }
    std::vector<std::tuple<std::string, int>> getMerklePath(Content*);
    bool verify();
    bool verifyContent(Content*);
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
