#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

#include "merkle/content.h"
#include "merkle/tree.h"
#include <nlohmann/json.hpp>

#include <vector>

class CLI {
public:
    CLI() {
	initialize();
    }

    int start(int, char**);
private:
    void initialize();

    // Merkle Tree Wrappers
    std::vector<Content> getContentListForPath(std::string);
    MerkleTree constructMerkleTree(std::vector<Content>);

    // Standard Output Helpers
    void printTreeStats(MerkleTree, std::vector<Content>);
    void printMerklePathForContent(MerkleTree t, Content c);
    void printUsage();

    // Command Line Operations
    void handleAdd(std::basic_string<char>);
    void handleRemove(std::basic_string<char> input);
    void handleList();    

    // Storage Helpers
    void persist(std::vector<Content> c, std::string root);
    nlohmann::json readFile(std::string);    
    void writeToFile(std::string, nlohmann::json);

    // Command Line Arguments
    enum _arguments { INVALID, ADD, LIST, REMOVE };
    std::map<std::string, _arguments> _args;
};

#endif
