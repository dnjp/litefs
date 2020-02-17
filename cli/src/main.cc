#include "merkle/content.h"
#include "merkle/tree.h"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main()
{

    // get directory from user
    std::string path;
    std::cout << "Enter the path to the directory you'd like to encrypt -> ";
    std::cin >> path;

    // read all file names in directory
    std::vector<Content> list;
    for (auto& entry : fs::recursive_directory_iterator(path)) {
        if (!fs::is_directory(entry)) {
            Content c = Content(fs::absolute(entry.path()).string());
            list.push_back(c);
        }
    }

    MerkleTree t = MerkleTree(list);

    std::string root = t.getMerkleRoot();
    std::cout << "root: " << root << std::endl;
    std::cout << "tree size: " << t.getLeafs().size() << std::endl;
    std::cout << "tree valid: " << (t.verify() == 1 ? "true" : "false")
              << std::endl;

    for (int i = 0; i < list.size(); i++) {
        Content c = list[i];
        std::cout << "content #" << i + 1
                  << " valid: " << (t.verifyContent(c) == 1 ? "true" : "false")
                  << std::endl;
    }

    auto mpath = t.getMerklePath(list.back());
    std::cout << "path size: " << mpath.size() << std::endl;
    for (auto p : mpath) {
        auto hash = std::get<0>(p);
        auto idx = std::get<1>(p);
        std::cout << idx << ": " << hash << std::endl;
    }

    return 0;
}
