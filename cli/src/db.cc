#include "cli/db.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

nlohmann::json DB::readAll() {
    std::ifstream i(location);
    nlohmann::json j;
    i >> j;
    return j;
}

void DB::write(nlohmann::json j) {
    std::ofstream o(location);
    o << j << std::endl;
}

bool DB::shouldInit() {
    return !fs::exists(location);
}

void DB::init() {
    FILE * fPtr;
    fPtr = fopen(location.c_str(), "w");
    if (fPtr == NULL) {
	std::cout << "could not create db file" << std::endl;
	exit(EXIT_FAILURE);
    }
    fclose(fPtr);
    
    nlohmann::json j;
    write(j);
}

nlohmann::json DB::toJson(root e) {
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

root DB::fromJson(nlohmann::json jRoot) {
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
