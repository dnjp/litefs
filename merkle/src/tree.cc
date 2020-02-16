#include "merkle/tree.h"
#include "merkle/content.h"
#include <bits/stdc++.h>

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
    if (_leafs.size() % 2 == 1) {
        std::string hash = _leafs[_leafs.size() - 1]->calculateHash();
        Content c = _leafs[_leafs.size() - 1]->content;
        Node* node = new Node(hash, c, true, true, this);
        _leafs.push_back(node);
    }
    buildRoot();
}

void MerkleTree::rebuild()
{
    std::vector<Content> contents;
    for (Node* n : _leafs) {
        contents.push_back(n->content);
    }
    build(contents);
}

void MerkleTree::buildRoot()
{
    for (int i = 0; i < _leafs.size(); i += 2) {
        int left = i;
        int right = i + 1;
        if (i + 1 == _leafs.size()) {
            right = i;
        }
        std::string lHash = _leafs[left]->calculateHash();
        std::string rHash = _leafs[right]->calculateHash();

        // create new hash with merged contents of lHash and rHash
        std::string cHash = lHash.append(rHash);

        // create new node with the hashed hash
        Hash hash = Hash(cHash);
        Node* n = new Node(_leafs[left], _leafs[right], hash, this);

        _leafs.push_back(n);
        _leafs[left]->parent = n;
        _leafs[right]->parent = n;

        if (_leafs.size() == 2) {
            _root = n;
            return;
        }
    }
    return buildRoot();
}

std::vector<std::tuple<std::string,int>> MerkleTree::getMerklePath(Content content)
{
    std::vector<std::tuple<std::string,int>> merklePath;
    for (Node* node : _leafs) {
        if (node->content != content) {
            return merklePath;
        }
        Node* parent = node->parent;
        while (parent != NULLPTR) {
            if (parent->left->calculateHash() == parent->calculateHash()) {
                merklePath.push_back({parent->right->calculateHash(), 1});
            } else {
                merklePath.push_back({parent->left->calculateHash(), 0});		
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

// TODO
bool MerkleTree::verifyContent(Content) { return false; }
