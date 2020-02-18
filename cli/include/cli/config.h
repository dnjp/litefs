#ifndef __CONFIF_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

#include "cli/db.h"

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
