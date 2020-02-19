#ifndef __DB_H_INCLUDED__
#define __DB_H_INCLUDED__

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

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

class DB {
public:
    DB() {}
    DB(std::string loc) : location(loc) {}
    nlohmann::json readAll();    

    void setLocation(std::string loc) {
	location = loc;
    }
    
    void write(nlohmann::json);
    bool shouldInit();
    void init();
    std::string location;


    nlohmann::json toJson(root);
    root fromJson(nlohmann::json);
};

#endif
