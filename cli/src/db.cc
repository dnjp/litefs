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
