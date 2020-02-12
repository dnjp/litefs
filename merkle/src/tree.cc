#include "merkle/tree.h"
#include "merkle/content.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/sha.h>

MerkleTree::MerkleTree(std::vector<Content> contents)
{
    if (contents.size() == 0) {
        return;
    }
    for (Content c : contents) {
        auto hash = c.calculateHash();
        Node* node = new Node(hash, c, true, this);
        _leafs.push_back(node);
    }
    if (_leafs.size() % 2 == 1) {
        auto hash = _leafs[_leafs.size() - 1]->getHash();
        auto c = _leafs[_leafs.size() - 1]->getContent();
        Node* node = new Node(hash, c, true, true, this);
        _leafs.push_back(node);
    }
    buildRoot();
}

std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>
    MerkleTree::createHashFromHash(
        std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE * 2> arr)
{
    std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> digest;
    CryptoPP::HexEncoder encoder;
    CryptoPP::SHA256 hash;

    CryptoPP::ArraySource(arr.data(), arr.size(), true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::ArraySink(
                digest.data(), CryptoPP::SHA256::DIGESTSIZE)));
    return digest;
}

void MerkleTree::buildRoot()
{
    for (int i = 0; i < _leafs.size(); i += 2) {
        int left = i;
        int right = i + 1;
        if (i + 1 == _leafs.size()) {
            right = i;
        }
        std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> lHash
            = _leafs[left]->getHash();
        std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> rHash
            = _leafs[right]->getHash();
        // create new array with merged contents of lHash and rHash
        std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE * 2> cHash;
        int shaSize = CryptoPP::SHA256::DIGESTSIZE;
        for (int i = 0; i < shaSize; i++) {
            cHash[i] = lHash[i];
        }
        for (int i = 0; i < shaSize; i++) {
            cHash[shaSize + i] = rHash[i];
        }

        std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE> hash
            = createHashFromHash(cHash);
        // create new node with the hash from previous function
	Node n = new Node(_leafs[left], _leafs[right], hash, this);

	_leafs.push_back(&n);
        _leafs[left]->setParent(&n);
        _leafs[right]->setParent(&n);	
        // if length of _leafs == 2, return just the new node
        if (_leafs.size() == 2) {
	    _root = &n;
	    return;
        }
    }
    return buildRoot();
}

std::vector<std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>>
    MerkleTree::getMerklePath(Content)
{
}

void MerkleTree::rebuild() {}

void MerkleTree::rebuildWithContent(std::vector<Content> content) {}

bool MerkleTree::verify() {}
