#ifndef __DB_H_INCLUDED__
#define __DB_H_INCLUDED__

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

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
};

#endif
