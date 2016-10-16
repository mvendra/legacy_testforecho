
#include "test_testforecho_second.h"

#include "testforecho.h"

bool test_testforecho_second(){

#define TEST_FLAG(BOOL_EXPR) if (!BOOL_EXPR) { std::cout << "Incorrect flag!" << std::endl; return false; }

    // TEST_EX
    {
        T4E_MAKE_0(p, {throw 1;})
        bool ret {test_ex<int>("Must throw int", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        bool ret {test_eq("Must be equal", 1, 1)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EX with capture
    {
        int o = 9;
        T4E_MAKE_1(p, int, o, { if (o == 9) {throw 1;} })
        bool ret {test_ex<int>("Must throw int - single capture", T4E_GET(p))};
        TEST_FLAG(ret)
    }

    // TEST_EX with double capture
    {
        int v1 {1};
        char v2 {'a'};

        T4E_MAKE_2(p, int, v1, char, v2, if (v1 == 1){ if (v2 == 'a'){ throw 1; }} )
        bool ret {test_ex<int>("Must throw int - from double capture", T4E_GET(p))};
        TEST_FLAG(ret)

    }

    return true;

}
