#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class MerkleTree;
class Content;

// internal
#include "merkle/content.h"
#include "merkle/hash.h"
#include "merkle/tree.h"

/*
 * The `Node` class is the fundamental building block of the merkle tree. A
 * `Node` contains data handles to its parent, sibling nodes, and the tree that
 * owns it.
 */
class Node {
public:
    // The primary constructor for a `Node`
    Node(std::string h, Content c, bool isLeaf, MerkleTree* t)
        : hash(h)
        , content(c)
        , _leaf(isLeaf)
        , tree(t)
    {
    }

    // The constructor for a duplicate `Node` to maintain a balanced tree
    Node(std::string h, Content c, bool isLeaf, bool dup, MerkleTree* t)
        : hash(h)
        , content(c)
        , _leaf(isLeaf)
        , _dup(dup)
        , tree(t)
    {
    }

    /* 
     * The constructor for instantiating Nodes to build out the lower levels of
     * the tree
     */
    Node(Node* l, Node* r, std::string h, MerkleTree* t)
        : left(l)
        , right(r)
        , hash(h)
        , tree(t)
    {
    }

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
