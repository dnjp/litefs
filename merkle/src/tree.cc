#include "merkle/tree.h"
#include "merkle/content.h"
#include <bits/stdc++.h>

MerkleTree::MerkleTree(std::vector<Content> contents) { build(contents); }

void MerkleTree::build(std::vector<Content> contents)
{
    if (contents.size() == 0) {
        return;
    }
    for (Content c : contents) {
        std::string hash = c.calculateHash();
        Node* node = new Node(hash, c, true, this);
        _leafs.push_back(node);
    }

    // ensures we always have an even number of nodes
    if (_leafs.size() % 2 == 1) {
        std::string hash = _leafs[_leafs.size() - 1]->calculateHash();
        Content c = _leafs[_leafs.size() - 1]->content;
        Node* node = new Node(hash, c, true, true, this);
        _leafs.push_back(node);
    }
    buildRoot(_leafs);
}

void MerkleTree::buildRoot(std::vector<Node*> nl)
{
    std::vector<Node*> nodes;
    for (int i = 0; i < nl.size(); i += 2) {
        int left = i;
        int right = i + 1;
        if (i + 1 == nl.size()) {
            right = i;
        }
        std::string lHash = nl[left]->calculateHash();
        std::string rHash = nl[right]->calculateHash();

        // create new hash with merged contents of lHash and rHash
        std::string cHash = lHash.append(rHash);

        // create new node with the hashed hash
        Hash hash = Hash(cHash);
        Node* n = new Node(nl[left], nl[right], hash, this);

        nodes.push_back(n);
        nl[left]->parent = n;
        nl[right]->parent = n;

        if (nl.size() == 2) {
            _root = n;
            _merkleRoot = n->calculateHash();
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
        if (node->content != content) {
            return merklePath;
        }
        Node* parent = node->parent;
        while (parent != NULLPTR) {
            if (parent->left->calculateHash() == parent->calculateHash()) {
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

void MerkleTree::rebuildWithContent(std::vector<Content> contents)
{
    build(contents);
    _merkleRoot = _root->calculateHash();
}

bool MerkleTree::verify()
{
    std::string hash = _root->verify();
    return _root->calculateHash() == hash;
}

bool MerkleTree::verifyContent(Content)
{
    for (Node* node : _leafs) {
        Node* parent = node->parent;
        while (parent != NULLPTR) {
            std::string rHash = parent->right->calculateHash();
            std::string lHash = parent->left->calculateHash();
            std::string cHash = lHash.append(rHash);
            Hash hash(cHash);
            hash.final();
            std::string digest = hash.toString();
            if (digest != parent->calculateHash()) {
                return false;
            }
            parent = parent->parent;
        }
        return true;
    }
    return false;
}

void MerkleTree::rebuild()
{
    std::vector<Content> contents;
    for (Node* n : _leafs) {
        contents.push_back(n->content);
    }
    build(contents);
}
