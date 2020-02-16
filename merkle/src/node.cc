#include "merkle/node.h"


Node::Node(Hash hash, Content content, bool leaf, MerkleTree* tree)
{
    this->hash = hash;
    this->content = content;
    this->_leaf = leaf;
    this->_tree = tree;
}

Node::Node(Hash hash, Content content, bool leaf, bool dup, MerkleTree* tree)
{
    this->hash = hash;
    this->content = content;
    this->_leaf = leaf;
    this->_dup = dup;
    this->_tree = tree;
}

Node::Node(Node* left, Node* right, Hash hash, MerkleTree* tree)
{
    this->left = left;
    this->right = right;
    this->hash = hash;
    this->_tree = tree;
}

std::string Node::verify()
{
    if (_leaf) {
        return content.calculateHash();
    }
    std::string lHash = left->verify();
    std::string rHash = right->verify();
    std::string tHash = _tree->getMerkleRoot();

    // add rightBytes to leftBytes
    std::string cHash = lHash.append(rHash);

    // add the result to the hash
    Hash hash = Hash(cHash);
    hash.final();
    return hash.toString();
}

std::string Node::calculateHash()
{
    if (_leaf) {
        return content.calculateHash();
    }

    // only call final() once
    if (!_digest.empty()) {
	return _digest;
    }

    std::string lHash = left->calculateHash();
    std::string rHash = left->calculateHash();
    std::string cHash = lHash.append(rHash);

    Hash hash = Hash(cHash);
    hash.final();
    _digest = hash.toString();
    return _digest;
}
