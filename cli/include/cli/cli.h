#ifndef __CLI_H_INCLUDED__
#define __CLI_H_INCLUDED__

// internal
#include "cli/config.h"
#include "cli/db.h"
#include "merkle/content.h"
#include "merkle/tree.h"
#include "server/server.h"
#include "server/endpoint.h"

// external
#include <nlohmann/json.hpp>

// system
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

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
    void printMerklePathForContent(MerkleTree t, Content c);
    void printUsage();

    // Command Line Operations
    void handleAdd(std::vector<std::string>);
    void handleRemove(std::basic_string<char> input);
    void handleList();
    void handleServe(std::basic_string<char> input);
    std::vector<Endpoint<std::string>> getEndpoints(
        std::string host, int port, root r, std::string hash);

    // General Helpers
    void addDirectory(std::string);

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

    // Handle async code
    std::mutex _mutex;
    std::condition_variable _cond;
    bool _ready = false;
};

#endif
