
#include "test_testforecho.h"

#include <iostream>

int main(int argc, char **argv){

    (void)argc; (void)argv;

    std::cout << "testforecho test app" << std::endl;
    if (test_testforecho()){
        std::cout << "all testforecho self-tests passed" << std::endl;
    } else {
        std::cout << "testforecho self tests: failures detected" << std::endl;
    }

    return 0;
}
