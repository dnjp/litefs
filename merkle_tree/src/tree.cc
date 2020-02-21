// internal
#include "merkle/tree.h"
#include "merkle/content.h"

// system
#include <bits/stdc++.h>

// The MerkleTree constructor takes a vector of contents to build the tree.
MerkleTree::MerkleTree(std::vector<Content> contents)
{
    _contents = contents;
    build(contents);
}

/*
 * `build()` takes the vector of contents and builds the tree, taking care to
 * duplicate a node if the conents are not even.
 */
void MerkleTree::build(std::vector<Content> contents)
{
    if (contents.size() == 0) {
        return;
    }
    for (Content c : contents) {
        std::string hash = c.calculateHash();
        _leafs.push_back(std::make_unique<Node>(hash, c, true, this));
    }

    // make duplicate to ensure we always have an even number of nodes
    if (_leafs.size() % 2 == 1) {
        std::string hash = _leafs.back()->hash;
        Content c = _leafs.back()->content;
        _leafs.push_back(std::make_unique<Node>(hash, c, true, true, this));
    }

    buildRoot(getNodeDataHandles());
}

std::vector<Node*> MerkleTree::getNodeDataHandles()
{
    std::vector<Node*> nodeHandles;
    for (std::unique_ptr<Node>& n : _leafs) {
        nodeHandles.push_back(n.get());
    }
    return nodeHandles;
}

/*
 * `buildRoot()` takes a vector of data handles to `Nodes` and recursively
 * iterates through them to construct the tree from the bottom up.
 */
void MerkleTree::buildRoot(std::vector<Node*> handles)
{
    std::vector<Node*> nodes;
    for (int i = 0; i < handles.size(); i += 2) {
        int left = i;
        int right = i + 1;
        if (i + 1 == handles.size()) {
            right = i;
        }
        std::string lHash = handles[left]->hash;
        std::string rHash = handles[right]->hash;

        // create new hash with joined contents of lHash and rHash
        std::string cHash = lHash + rHash;

        // create new node with the hashed value
        Hash hash = Hash(cHash);
        hash.final();
        Node* n
            = new Node(handles[left], handles[right], hash.calculate(), this);

        nodes.push_back(n);
        handles[left]->parent = n;
        handles[right]->parent = n;

        if (handles.size() == 2) {
            _root = n;
            _merkleRoot = n->hash;
            return;
        }
    }
    buildRoot(nodes);
}

/*
 * `verify()` verifies that the resulting hash of constructing the tree matches
 * the hash of the root node.
 */
bool MerkleTree::verify() { return _merkleRoot.compare(_root->verify()) == 0; }

/*
 * `verifyContent()` takes a `Content` object and traverses the tree to see if
 * it can find content within it.
 */
bool MerkleTree::verifyContent(Content* content)
{
    for (std::unique_ptr<Node>& l : _leafs) {
        // ensures that content matches one present in tree
        if (l->content != *content) {
            continue;
        }

        // validates hashes are valid for tree
        Node* leaf = l.get();
        Node* parent = leaf->parent;
        while (parent != nullptr) {
            std::string lHash = parent->left->calculateHash();
            std::string rHash = parent->right->calculateHash();

            Hash hash(lHash + rHash);
            hash.final();
            std::string digest = hash.calculate();

            if (digest.compare(parent->calculateHash()) != 0) {
                return false;
            }

            // move to parent node
            parent = parent->parent;
        }
        return true;
    }
    return false;
}

/*
 * `getMerklePath()` takes a `Content` object and returns an indexed path to the
 * content.
 */
std::vector<std::tuple<std::string, int>> MerkleTree::getMerklePath(
    Content* content)
{
    std::vector<std::tuple<std::string, int>> merklePath;
    for (std::unique_ptr<Node>& n : _leafs) {
        if (n->content != *content) {
            continue;
        }
        Node* node = n.get();
        Node* parent = node->parent;
        while (parent != NULLPTR) {
	    std::tuple<std::string, int> item;
            if (parent->left->calculateHash().compare(parent->calculateHash())
                == 0) {
		item = { parent->right->calculateHash(), 1 };
                merklePath.push_back(item);
            } else {
		item = { parent->right->calculateHash(), 0 };
                merklePath.push_back(item);
            }
            node = parent;
            parent = node->parent;
        }
    }
    return merklePath;
}
