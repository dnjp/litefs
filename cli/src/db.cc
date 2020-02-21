// internal
#include "cli/db.h"

// system
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

/*
 * `init()` creates the local json database and initializes it with a null JSON
 * object
 */
void DB::init()
{
    FILE* fPtr;
    fPtr = fopen(location.c_str(), "w");
    if (fPtr == NULL) {
        std::cout << "could not create db file" << std::endl;
        exit(EXIT_FAILURE);
    }
    fclose(fPtr);

    nlohmann::json j;
    write(j);
}

/*
 * `shouldInit()` determines if the local database already exists
 */
bool DB::shouldInit() { return !fs::exists(location); }

/*
 * `readAll()` reads the entire contents of the json database
 */
nlohmann::json DB::readAll()
{
    std::ifstream i(location);
    nlohmann::json j;
    i >> j;
    return j;
}

/*
 * `write()` takes a json object and writes it to the users database
 */
void DB::write(nlohmann::json j)
{
    std::ofstream o(location);
    o << j << std::endl;
}

/*
 * `toJson()` is a utility function that takes a `root` struct and serializes it
 * into a json object
 */
nlohmann::json DB::toJson(root e)
{
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

/*
 * `fromJson()` is a utility function that deserializes a json object into a
 * `root` struct object
 */
root DB::fromJson(nlohmann::json jRoot)
{
    root e;
    jRoot.at("root_path").get_to(e.root_path);

    std::vector<nlohmann::json> contents
        = jRoot["contents"].get<nlohmann::json>();
    for (auto c : contents) {
        elem el;
        c.at("content_hash").get_to(el.content_hash);
        c.at("content_path").get_to(el.content_path);
        e.contents.push_back(el);
    }

    return e;
}
