#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

// local
#include "merkle/content.h"
#include "cli/db.h"
#include "cli/config.h"
#include "merkle/tree.h"

// external
#include <nlohmann/json.hpp>

// system
#include <vector>

class CLI {
public:
    CLI() {
	// accepted commands
        _args["add"] = ADD;
        _args["ls"] = LIST;
        _args["rm"] = REMOVE;
    }

    int start(int, char**);
private:

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

    // Command Line Arguments
    enum _arguments { INVALID, ADD, LIST, REMOVE };
    std::map<std::string, _arguments> _args;

    // Database
    DB _db;
    void checkDB();

    // Configuration
    Config _cf;
    void checkConfig();
};

#endif
