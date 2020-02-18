#include "cli/cli.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void CLI::initialize() {
    _args["add"] = ADD;
    _args["ls"] = LIST;
    _args["rm"] = REMOVE;        
}

void CLI::persist(std::vector<Content> c, std::string root)
{
    std::vector<std::string> contents;    
    for (auto content : c) {
	contents.push_back(content.calculateHash());
    }
    nlohmann::json j = readFile("file.json");
    
    // nlohmann::json j;
    j[root] = contents;
    writeToFile("file.json", j);
}

nlohmann::json CLI::readFile(std::string path) {
    std::ifstream i(path);
    nlohmann::json j;
    i >> j;
    return j;
}

void CLI::writeToFile(std::string path, nlohmann::json j) {
    std::ofstream o(path);
    o << j << std::endl;
}

// get directory from user
std::vector<Content> CLI::getContentListForPath(std::string path) {

    // read all file names in directory
    std::vector<Content> list;
    for (auto& entry : fs::recursive_directory_iterator(path)) {
        if (!fs::is_directory(entry)) {
            Content c = Content(fs::absolute(entry.path()).string());
            list.push_back(c);
        }
    }

    return list;
}

MerkleTree CLI::constructMerkleTree(std::vector<Content> list) {
    MerkleTree t = MerkleTree(list);
    return t;
}

void CLI::printTreeStats(MerkleTree t, std::vector<Content> list) {
    std::string root = t.getMerkleRoot();
    std::cout << "\n";

    if (t.verify() == false) {
	std::cout << "error: tree is invalid." << std::endl;
	return;
    }
    std::cout << "root hash: " << root << std::endl;
    std::cout << "tree size: " << t.getLeafs().size() << std::endl;

    for (int i = 0; i < list.size(); i++) {
        Content c = list[i];
	std::cout << "file: " << c.getPath() << std::endl;
	std::cout << "      " << c.calculateHash() << std::endl;
	std::cout << "\n";
    }    
}

void CLI::printMerklePathForContent(MerkleTree t, Content c) {
    std::vector<std::tuple<std::string, int>> mpath = t.getMerklePath(c);
    std::cout << "path size: " << mpath.size() << std::endl;
    for (auto p : mpath) {
        auto hash = std::get<0>(p);
        auto idx = std::get<1>(p);
        std::cout << idx << ": " << hash << std::endl;
    }    
}

void CLI::printUsage() {
    std::cout << "usage: litefs <command> [<args>]" << std::endl;
    std::cout << "\n";
    std::cout << "These are the common lfs commands:" << std::endl;
    std::cout << "\n";
    std::cout << "    add    <directory>   Add directory to stored stored hashes." << std::endl;
    std::cout << "\n";
    std::cout << "    ls                   List the hashes that are currently stored." << std::endl;
    std::cout << "\n";
    std::cout << "    rm     <hash>        Remove the selected hash from storage." << std::endl;
    std::cout << "\n";
}

void CLI::handleAdd(std::basic_string<char> input) {
    std::string path(input);
    std::vector<Content> list = getContentListForPath(path);
    MerkleTree t = constructMerkleTree(list);
    persist(list, t.getMerkleRoot());
    printTreeStats(t, list);
}

void CLI::handleRemove(std::basic_string<char> input) {
    std::string hash(input);
    nlohmann::json j = readFile("file.json");    
    j.erase(hash);
    writeToFile("file.json", j);
}

void CLI::handleList() {
    nlohmann::json j = readFile("file.json");
    std::cout << j.dump(4) << std::endl;
}



int CLI::start(int argc, char* argv[]) {
    if (argc == 1) {
	std::cout << "no command supplied.\n" << std::endl;
	printUsage();
	std::cout << "\n";
	return 1;
    }

    std::string arg(argv[1]);
    switch (_args[arg]) {
    case ADD:

        if (argc != 3) {
            std::cout << "please supply a path to the [add] command.\n" << std::endl;
            printUsage();
            std::cout << "\n";
	    return 1;
        }

	handleAdd(argv[2]);
        break;
    case LIST:
	handleList();
        break;
    case REMOVE:
        if (argc != 3) {
            std::cout << "please supply a hash to the [rm] command.\n" << std::endl;
            printUsage();
            std::cout << "\n";
	    return 1;
        }
	handleRemove(argv[2]);
        break;
    default:

	std::cout << arg << " is not a valid command.\n" << std::endl;
	printUsage();
	std::cout << "\n";
	return 1;
    }

    return 0;
}
