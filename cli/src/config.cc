// internal
#include "cli/config.h"

// system
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace fs = std::filesystem;

/*
 * The `Config` retrievs the users $HOME variable and initialzes the
 * configuration default location
 */
Config::Config()
{
    char* h = std::getenv("HOME");
    std::string home(h);
    std::string cPath = home + "/.lfs.conf";
    location = cPath;
}

/*
 * `init()` writes the default configuration file
 */
void Config::init()
{
    FILE* fPtr;
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

/*
 * `getDBLocation()` retrieves the correct database location from the users
 * configuration file
 */
std::string Config::getDBLocation()
{
    nlohmann::json j = readAll();
    std::string dbLoc = j["db_location"].get<std::string>();
    return dbLoc;
}
