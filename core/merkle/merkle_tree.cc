#include "merkle_tree.h"
#include "content.h"

MerkleTree::MerkleTree(std::vector<Content> content) {}

std::vector<std::vector<unsigned char>> MerkleTree::getMerklePath(Content) {}

void MerkleTree::rebuild() {}

void MerkleTree::rebuildWithContent(std::vector<Content> content) {}

bool MerkleTree::verify() {}