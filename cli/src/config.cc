#include "cli/config.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


namespace fs = std::filesystem;

Config::Config() {
    char* h = std::getenv("HOME");
    std::string home(h);
    std::string cPath = home + "/.lfs.conf";
    location = cPath;
}

void Config::init() {
    FILE * fPtr;
    fPtr = fopen(location.c_str(), "w");
    if (fPtr == NULL) {
	std::cout << "could not create config file" << std::endl;
	exit(EXIT_FAILURE);
    }
    fclose(fPtr);

    char* h = std::getenv("HOME");
    std::string home(h);
    std::string dbLoc = home + "/.lfs.db";
    
    nlohmann::json j;
    j["db_location"] = dbLoc;
    j["port"] = 3000;
    write(j);
}

std::string Config::getDBLocation() {
    nlohmann::json j = readAll();
    std::string dbLoc = j["db_location"].get<std::string>();
    return dbLoc;
}
