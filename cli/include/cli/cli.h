#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

// local
#include "cli/config.h"
#include "cli/db.h"
#include "merkle/content.h"
#include "merkle/tree.h"
#include "server/server.h"

// external
#include <nlohmann/json.hpp>

// system
#include <vector>

class CLI {
public:
    CLI()
    {
        // accepted commands
        _args["add"] = ADD;
        _args["status"] = LIST;
        _args["rm"] = REMOVE;
        _args["serve"] = SERVE;	
    }

    int start(int, char**);

private:
    // Merkle Tree Wrappers
    std::vector<Content> getContentListForPath(std::string);
    MerkleTree constructMerkleTree(std::vector<Content>);
    bool verifyContents(root, std::string);

    // Standard Output Helpers
    void printTreeStats(MerkleTree, std::vector<Content>);
    void printMerklePathForContent(MerkleTree t, Content c);
    void printUsage();

    // Command Line Operations
    void handleAdd(std::basic_string<char>);
    void handleRemove(std::basic_string<char> input);
    void handleList();
    void handleServe(std::basic_string<char> input);

    // Storage Helpers
    void persist(std::vector<Content> c, std::string root, std::string);

    // Command Line Arguments
    enum _arguments { INVALID, ADD, LIST, REMOVE, SERVE };
    std::map<std::string, _arguments> _args;

    // Database
    DB _db;
    void checkDB();

    // Configuration
    Config _cf;
    void checkConfig();
};

#endif
