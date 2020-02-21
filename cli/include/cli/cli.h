#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

// internal
#include "cli/config.h"
#include "cli/db.h"
#include "merkle/content.h"
#include "merkle/tree.h"
#include "server/server.h"

// external
#include <nlohmann/json.hpp>

// system
#include <vector>
#include <memory>

/*
 * CLI contains the functionality for controlling interaction with the user
 */
class CLI {
public:
    CLI()
    {
        // accepted commands
        _args["add"] = ADD;
        _args["status"] = LIST;
        _args["rm"] = REMOVE;
        _args["serve"] = SERVE;
        _args["help"] = HELP;

	_db = std::make_unique<DB>();
	_cf = std::make_unique<Config>();	
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
    std::vector<endpoint> getEndpoints(
        std::string host, int port, root r, std::string hash);

    // Storage Helpers
    void persist(std::vector<Content> c, std::string root, std::string);

    // Command Line Arguments
    enum _arguments { INVALID, ADD, LIST, REMOVE, SERVE, HELP };
    std::map<std::string, _arguments> _args;

    // Database
    std::unique_ptr<DB> _db;
    void checkDB();

    // Configuration
    std::unique_ptr<Config> _cf;
    void checkConfig();
};

#endif
