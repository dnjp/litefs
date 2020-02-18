#include "cli/cli.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

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
    std::cout << "usage: litefs [add] <path>" << std::endl;
}

void CLI::handleAdd(std::basic_string<char> input) {
    std::string path(input);
    std::vector<Content> list = getContentListForPath(path);
    MerkleTree t = constructMerkleTree(list);
    printTreeStats(t, list);
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
    default:
	std::cout << arg << " is not a valid command.\n" << std::endl;
	printUsage();
	std::cout << "\n";
	return 1;
    }

    return 0;
}
