#include "merkle/tree.h"
#include "merkle/content.h"
#include <bits/stdc++.h>

MerkleTree::MerkleTree(std::vector<Content*> contents) { build(contents); }

void MerkleTree::build(std::vector<Content*> contents)
{
    if (contents.size() == 0) {
        return;
    }
    for (Content* c : contents) {
        std::string hash = c->calculateHash();
        Node* node = new Node(hash, c, true, this);
        _leafs.push_back(node);
    }

    // make duplicate to ensure we always have an even number of nodes
    if (_leafs.size() % 2 == 1) {
        std::string hash = _leafs.back()->hash;
        Content* c = _leafs.back()->content;
        Node* node = new Node(hash, c, true, true, this);
        _leafs.push_back(node);
    }
    buildRoot(_leafs);
}

void MerkleTree::buildRoot(std::vector<Node*> leaves)
{
    std::vector<Node*> nodes;
    for (int i = 0; i < leaves.size(); i += 2) {
        int left = i;
        int right = i + 1;
        if (i + 1 == leaves.size()) {
            right = i;
        }
        std::string lHash = leaves[left]->hash;
        std::string rHash = leaves[right]->hash;

        // create new hash with merged contents of lHash and rHash
        std::string cHash = lHash + rHash;

        // create new node with the hashed value
        Hash hash = Hash(cHash);
        hash.final();
        Node* n = new Node(leaves[left], leaves[right], hash.calculate(), this);

        nodes.push_back(n);
        leaves[left]->parent = n;
        leaves[right]->parent = n;

        if (leaves.size() == 2) {
            _root = n;
            _merkleRoot = n->hash;
            return;
        }
    }
    buildRoot(nodes);
}

std::vector<std::tuple<std::string, int>> MerkleTree::getMerklePath(
    Content content)
{
    std::vector<std::tuple<std::string, int>> merklePath;
    for (Node* node : _leafs) {
        if (node->content != &content) {
            return merklePath;
        }
        Node* parent = node->parent;
        while (parent != NULLPTR) {
            if (parent->left->calculateHash().compare(parent->calculateHash())
                == 0) {
                merklePath.push_back({ parent->right->calculateHash(), 1 });
            } else {
                merklePath.push_back({ parent->left->calculateHash(), 0 });
            }
            node = parent;
            parent = node->parent;
        }
    }
    return merklePath;
}

void MerkleTree::rebuildWithContent(std::vector<Content*> contents)
{
    build(contents);
    _merkleRoot = _root->calculateHash();
}

bool MerkleTree::verify() { return _merkleRoot.compare(_root->verify()) == 0; }

bool MerkleTree::verifyContent(Content* content)
{
    for (Node* leaf : _leafs) {
        // ensures that content matches one present in tree
        if (leaf->content != content) {
            continue;
        }

        // validates hashes are valid for tree
        Node* parent = leaf->parent;
        while (parent != nullptr) {
	    // std::cout << "left: " << parent->left->content->getPath() << std::endl; // c1
	    // std::cout << "right: " << parent->right->content->getPath() << std::endl;  // c2   
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

void MerkleTree::rebuild()
{
    std::vector<Content*> contents;
    for (Node* n : _leafs) {
        contents.push_back(n->content);
    }
    build(contents);
}
