
#include "test_testforecho.h"

#include "test_testforecho_first.h"
#include "test_testforecho_second.h"

bool test_testforecho(){

    bool total {true};

    total &= test_testforecho_first();
    total &= test_testforecho_second();

    return total;

}
