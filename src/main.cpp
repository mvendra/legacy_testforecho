
#include "test_testforecho.h"

#include <iostream>

int main(int argc, char **argv){

    (void)argc; (void)argv;

    std::cout << "testforecho test app" << std::endl;
    unsigned int r = test_testforecho();
    if (r == 0){
        std::cout << "all testforecho self-tests passed" << std::endl;
    } else {
        std::cout << "testforecho self tests: " << r << " failures detected" << std::endl;
    }

    return 0;
}
