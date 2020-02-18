#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

#include "merkle/content.h"
#include "merkle/tree.h"

#include <vector>

class CLI {
public:
    CLI() {
	initialize();
    }
    std::vector<Content> getContentListForPath(std::string);
    MerkleTree constructMerkleTree(std::vector<Content>);
    void printTreeStats(MerkleTree, std::vector<Content>);
    void printMerklePathForContent(MerkleTree t, Content c);
    void printUsage();
    void handleAdd(std::basic_string<char>);
    int start(int, char**);
private:
    void initialize() {
	_args["add"] = ADD;
    }
    enum _arguments { INVALID, ADD };
    std::map<std::string, _arguments> _args;
};

#endif
