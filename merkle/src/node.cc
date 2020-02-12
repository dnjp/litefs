#include "merkle/node.h"

Node::Node(std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> hash,
    Content content, bool leaf, MerkleTree* tree)
{
    _hash = hash;
    _content = content;
    _leaf = leaf;
    _tree = tree;
}

Node::Node(std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> hash,
    Content content, bool leaf, bool dup, MerkleTree* tree)
{
    _hash = hash;
    _content = content;
    _leaf = leaf;
    _dup = dup;
    _tree = tree;
}

Node::Node(Node* left, Node* right,
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> hash,
    MerkleTree* tree)
{
    _left = left;
    _right = right;
    _hash = hash;
    _tree = tree;
}

std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> Node::verify()
{
    // if (_leaf) {
    //     return content.calculateHash();
    // }
    // std::string rightBytes = right->verify();
    // std::string leftBytes = left->verify();
    // h = tree->getHash();

    // h := n.Tree.hashStrategy()
    // if _, err := h.Write(append(leftBytes, rightBytes...)); err != nil {
    // 	return nil, err
    // }

    // return h.Sum(nil), nil
}

std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> Node::calculateHash()
{
}
