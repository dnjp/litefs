#include "cli/cli.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    CLI cli = CLI();
    cli.start(argc, argv);

    return 0;
}
