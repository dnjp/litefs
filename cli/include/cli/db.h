#ifndef __DB_H_INCLUDED__
#define __DB_H_INCLUDED__

// external
#include <nlohmann/json.hpp>

// system
#include <string>
#include <vector>

/*
 * `elem` and `root` are internal representations of the `Content` objects,
 * `MerkleTree` root, and the hashes for all of the contents and nodes
 */
struct elem {
    std::string content_hash;
    std::string content_path;
};

struct root {
    std::string root_path;
    std::vector<elem> contents;
};

typedef struct elem elem;
typedef struct root root;

/*
 * The DB class reads and writes data from the users local json database
 */
class DB {
public:
    DB() {}
    DB(std::string loc)
        : location(loc)
    {
    }
    virtual nlohmann::json readAll();
    virtual void setLocation(std::string loc) { location = loc; }
    virtual void write(nlohmann::json);
    virtual bool shouldInit();
    virtual void init();

    nlohmann::json toJson(root);
    root fromJson(nlohmann::json);
    
    std::string location;
};

#endif
