#ifndef __CONFIF_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

// internal
#include "cli/db.h"

/*
 * Config inherits from DB as the configuration file is another type of
 * database. It overrides the `init()` function to initialize the configuration
 * file
 */
class Config : public DB {
public:
    Config();
    Config(std::string loc)
        : DB(loc)
    {
    }

    void init();
    std::string getDBLocation();
};

#endif
