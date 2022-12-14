
#include "test_legacy_testforecho.h"

#include "test_legacy_testforecho_first.h"
#include "test_legacy_testforecho_second.h"

unsigned int test_legacy_testforecho(){

    unsigned int total {0};

    total += test_legacy_testforecho_first();
    total += test_legacy_testforecho_second();

    return total;

}
