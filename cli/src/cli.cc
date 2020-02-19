#include "cli/cli.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace hash {

struct elem {
    std::string content_hash;
    std::string content_path;
};

struct root {
    std::string root_path;
    std::vector<elem> contents;
};

nlohmann::json toJson(root e) {
    nlohmann::json j;

    j["root_path"] = e.root_path;

    std::vector<nlohmann::json> elements;
    for (elem content : e.contents) {
	nlohmann::json elem;
	elem["content_hash"] = content.content_hash;
	elem["content_path"] = content.content_path;
	elements.push_back(elem);
    }

    j["contents"] = elements;

    return j;
}

root fromJson(nlohmann::json jRoot) {
    root e;
    jRoot.at("root_path").get_to(e.root_path);
    
    std::vector<nlohmann::json> contents = jRoot["contents"].get<nlohmann::json>();
    for (auto c : contents) {
        elem el;
        c.at("content_hash").get_to(el.content_hash);
        c.at("content_path").get_to(el.content_path);
	e.contents.push_back(el);
    }    

    return e;
}
}

void CLI::persist(std::vector<Content> c, std::string root, std::string path)
{
    nlohmann::json j = _db.readAll();

    hash::root e;
    e.root_path = path;
    for (auto content : c) {
	hash::elem l;
    	l.content_hash = content.calculateHash();
    	l.content_path = content.getPath();
    	e.contents.push_back(l);
    }

    j[root] = hash::toJson(e);;
    _db.write(j);
}

// get directory from user
std::vector<Content> CLI::getContentListForPath(std::string path)
{
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

MerkleTree CLI::constructMerkleTree(std::vector<Content> list)
{
    MerkleTree t = MerkleTree(list);
    return t;
}

void CLI::printTreeStats(MerkleTree t, std::vector<Content> list)
{
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

void CLI::printMerklePathForContent(MerkleTree t, Content c)
{
    std::vector<std::tuple<std::string, int>> mpath = t.getMerklePath(c);
    std::cout << "path size: " << mpath.size() << std::endl;
    for (auto p : mpath) {
        auto hash = std::get<0>(p);
        auto idx = std::get<1>(p);
        std::cout << idx << ": " << hash << std::endl;
    }
}

void CLI::printUsage()
{
    std::cout << "usage: litefs <command> <args>" << std::endl;
    std::cout << "\n";
    std::cout << "These are the common lfs commands:" << std::endl;
    std::cout << "\n";
    std::cout
        << "    add    <directory>   Add directory to stored stored hashes."
        << std::endl;
    std::cout << "\n";
    std::cout
        << "    status               List the hashes that are currently stored."
        << std::endl;
    std::cout << "\n";
    std::cout
        << "    rm     <hash>        Remove the selected hash from storage."
        << std::endl;
    std::cout << "\n";
    std::cout << "    serve  <hash>        Serve the specified hash for "
                 "network access"
              << std::endl;
    std::cout << "\n";
}

void CLI::handleServe(std::basic_string<char> input)
{
    std::string hash(input);
    nlohmann::json j = _db.readAll();

    // returns an array of json objects
    nlohmann::json contents = j[hash].get<nlohmann::json>();
    hash::root r = hash::fromJson(contents);

    std::cout << "root_hash: " << hash << std::endl;
    std::cout << "root_path: " << r.root_path << std::endl;
    std::cout << "contents: " << std::endl;
    for (auto c : r.contents) {
	std::cout << "    content_hash: " << c.content_hash << std::endl;
	std::cout << "    content_path: " << c.content_path << std::endl;	
    }
}

void CLI::handleAdd(std::basic_string<char> input)
{
    std::string path(input);
    std::string absPath = fs::absolute(path).string();
    std::vector<Content> list = getContentListForPath(absPath);

    MerkleTree t = constructMerkleTree(list);
    persist(list, t.getMerkleRoot(), absPath);
    printTreeStats(t, list);
}

void CLI::handleRemove(std::basic_string<char> input)
{
    std::string hash(input);
    nlohmann::json j = _db.readAll();
    j.erase(hash);
    _db.write(j);

    std::cout << "\n";
    std::cout << "removed hash: " << hash << std::endl;
    std::cout << "\n";
}

void CLI::handleList()
{
    nlohmann::json j = _db.readAll();
    std::cout << "\n";
    if (j.is_null() == true) {
        std::cout << "no files have been hashed" << std::endl;
    } else {
        std::cout << j.dump(4) << std::endl;
    }
    std::cout << "\n";
}

void CLI::checkConfig()
{
    if (_cf.shouldInit() == true) {
        std::cout << "\n";
        std::cout << "initializing configuration...  ";
        _cf.init();
        _db.setLocation(_cf.getDBLocation());
        std::cout << "done." << std::endl;
    }
}

void CLI::checkDB()
{
    if (_db.shouldInit() == true) {
        std::cout << "initializing database configuration...  ";
        _db.init();
        std::cout << "done." << std::endl;
        std::cout << "\n";
    }
}

int CLI::start(int argc, char* argv[])
{
    checkConfig();
    _db.setLocation(_cf.getDBLocation());
    checkDB();

    if (_db.shouldInit() == true) {
        std::cout << "initializing database configuration...  ";
        _db.init();
        std::cout << "done." << std::endl;
        std::cout << "\n";
    }

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
            std::cout << "please supply a path to the [add] command.\n"
                      << std::endl;
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
            std::cout << "please supply a hash to the [rm] command.\n"
                      << std::endl;
            printUsage();
            std::cout << "\n";
            return 1;
        }
        handleRemove(argv[2]);
        break;
    case SERVE:
        if (argc != 3) {
            std::cout << "please supply a hash to the [serve] command.\n"
                      << std::endl;
            printUsage();
            std::cout << "\n";
            return 1;
        }
        handleServe(argv[2]);
        break;
    default:

        std::cout << arg << " is not a valid command.\n" << std::endl;
        printUsage();
        std::cout << "\n";
        return 1;
    }

    return 0;
}
