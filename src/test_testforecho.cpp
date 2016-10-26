
#include "test_testforecho.h"

#include "test_testforecho_first.h"
#include "test_testforecho_second.h"

unsigned int test_testforecho(){

    unsigned int total {0};

    total += test_testforecho_first();
    total += test_testforecho_second();

    return total;

}
