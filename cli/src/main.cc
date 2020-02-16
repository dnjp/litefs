#include "merkle/content.h"
#include "merkle/tree.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int main()
{
    std::vector<Content> list;
    list.push_back(Content("Hello"));
    list.push_back(Content("Hi"));
    list.push_back(Content("Hey"));
    list.push_back(Content("Hola"));

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

    std::vector<Content> list2;
    list2.push_back(Content("Hello"));
    list2.push_back(Content("Hi"));
    list2.push_back(Content("Hey"));
    list2.push_back(Content("Hola"));

    MerkleTree t2 = MerkleTree(list2);

    std::string root2 = t2.getMerkleRoot();
    std::cout << "root: " << root2 << std::endl;
    std::cout << "tree size: " << t2.getLeafs().size() << std::endl;
    std::cout << "tree valid: " << (t2.verify() == 1 ? "true" : "false")
              << std::endl;

    for (int i = 0; i < list2.size(); i++) {
        Content c = list[i];
        std::cout << "content #" << i + 1
                  << " valid: " << (t2.verifyContent(c) == 1 ? "true" : "false")
                  << std::endl;
    }

    if (root2 == root) {
        std::cout << "roots match\n";
    } else {
        std::cout << "roots do not match\n";
    }

    return 0;
}
