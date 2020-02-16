#include "merkle/content.h"
#include "merkle/hash.h"
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <string>

int main()
{
    Content c("hello");
    Hash h(c.getMessage());
    std::cout << "verified: " << h.verify() << std::endl;
    std::cout << h.toString() << std::endl;

    h.final();
    
    std::cout << "verified: " << h.verify() << std::endl;
    std::cout << h.toString() << std::endl;

    return 0;
}
