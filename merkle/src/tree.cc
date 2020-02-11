#include "merkle/tree.h"
#include "merkle/content.h"

MerkleTree::MerkleTree(std::vector<Content> contents) {
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

// void MerkleTree::buildRoot() {
//     for (int i = 0; i < _leafs.size(); i += 2) {
// 	int left = i;
// 	int right = i + 1;
// 	if (i + 1 == _leafs.size()) {
// 	    right = i;
// 	}
	
//     }
// }

std::vector<std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>> MerkleTree::getMerklePath(Content) {}

void MerkleTree::rebuild() {}

void MerkleTree::rebuildWithContent(std::vector<Content> content) {}

bool MerkleTree::verify() {}
