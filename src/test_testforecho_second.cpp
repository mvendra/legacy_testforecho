
#include "test_testforecho_second.h"

#include "testforecho.h"

bool test_testforecho_second(){

#define TEST_FLAG(BOOL_EXPR) if (!BOOL_EXPR) { std::cout << "Incorrect flag!" << std::endl; return false; }

    // TEST_EX
    {
        T4E_MAKE(p, {throw 1;})
        bool ret {test_ex<int>("Must throw int", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        bool ret {test_eq("Must be equal", 1, 1)};
        TEST_FLAG(ret) // expected: true
    }

    return true;

}
