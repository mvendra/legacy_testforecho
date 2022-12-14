
#include "test_legacy_testforecho.h"

#include <iostream>

int main(int argc, char **argv){

    (void)argc; (void)argv;

    std::cout << "legacy_testforecho test app" << std::endl;
    unsigned int r = test_legacy_testforecho();
    if (r == 0){
        std::cout << "all legacy_testforecho self-tests passed" << std::endl;
    } else {
        std::cout << "legacy_testforecho self tests: " << r << " failures detected" << std::endl;
    }

    return 0;
}
