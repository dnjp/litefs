#ifndef __CONTENT_H_INCLUDED__
#define __CONTENT_H_INCLUDED__

// internal
#include "merkle/hash.h"

// system
#include <string>
#include <vector>

/*
 * Content represents a file that a user has submitted. It contains
 * functionality to generate a SHA256 hash of the contents of the selected file.
 */
class Content {
public:
    Content() {}
    Content(std::string path)
        : _path(path)
    {
    }

    std::string getPath() { return _path; }
    std::string calculateHash();

    bool operator==(const Content c) { return _path == c._path; }
    bool operator!=(const Content c) { return _path != c._path; }

private:
    std::string _path;
    Hash _hash = Hash();
    std::string _digest;
};

#endif
