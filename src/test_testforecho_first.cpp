
#include "test_testforecho_first.h"

#include "testforecho.h"

using namespace testforecho;

bool test_testforecho_first(){

#define TEST_FLAG(BOOL_EXPR) if (!BOOL_EXPR) { std::cout << "Incorrect flag!" << std::endl; return false; }

    #ifdef COMPILER_NO_CONCEPTS_SUPPORT
    PRINT_INFO("Using testforecho in compatibility mode (no param auto)")
    #endif

    ///////////////////
    // BOOL NOT WRAPPED
    ///////////////////

    #ifndef COMPILER_NO_CONCEPTS_SUPPORT
    // TEST
    {
        auto comp = [](auto p1, auto p2) { return (p1 != p2); };
        bool ret {test("Must be different", 5, 6, comp)};
        TEST_FLAG(ret) // expected: true
    }
    #endif // COMPILER_NO_CONCEPTS_SUPPORT

    // TEST_EX
    {
        T4E_MAKE_0(p, {throw 1;})
        bool ret {test_ex<int>("Must throw int", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        T4E_MAKE_0(p, {throw 1;})
        bool ret {test_no_ex<double>("Must NOT throw double", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        T4E_MAKE_0(p, {throw 'a';})
        bool ret {test_any_ex("Must throw something", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_NO_EX
    {
        T4E_MAKE_0(p, {/* i dont throw */})
        bool ret {test_any_no_ex("Must not throw anything", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_TRUE
    {
        bool ret {test_true("Must be true", !false)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_FALSE
    {
        bool ret {test_false("Must be false", !true)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        bool ret {test_eq("Must be equal", 1, 1)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NE
    {
        bool ret {test_ne("Must not be equal", 'p', 57)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GT
    {
        bool ret {test_gt("Must be greater than", 30, 20)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GE
    {
        bool ret {test_ge("Must be greater-or-equal", 10, 10)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_LT
    {
        bool ret {test_lt("Must be lesser than", 30, 80)};
        TEST_FLAG(ret);
    }

    // TEST_LE
    {
        bool ret {test_le("Must be lesser-or-equal", 9, 9)};
        TEST_FLAG(ret);
    }

    ///////////////
    // BOOL WRAPPED
    ///////////////

    #ifndef COMPILER_NO_CONCEPTS_SUPPORT
    // TEST
    {
        bool ret {true};
        auto comp = [](auto p1, auto p2) { return (p1 == p2); };
        test(ret, "Must be same", 1, 1, comp);
        TEST_FLAG(ret) // expected: true
    }
    #endif // COMPILER_NO_CONCEPTS_SUPPORT

    // TEST_EX
    {
        bool ret {true};
        T4E_MAKE_0(p, {throw 1;})
        test_ex<int>(ret, "Must throw int", T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        bool ret {true};
        T4E_MAKE_0(p, {throw 1;})
        test_no_ex<double>(ret, "Must NOT throw double", T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        bool ret {true};
        T4E_MAKE_0(p, {/* i dont throw */})
        test_any_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when no exception is thrown", T4E_GET(p));
        TEST_FLAG(!ret) // expected: false
    }

    // TEST_ANY_NO_EX
    {
        bool ret {true};
        T4E_MAKE_0(p_int, {throw 1;})
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when INT exception is thrown", T4E_GET(p_int));
        TEST_FLAG(!ret); // expected: false
        T4E_MAKE_0(p_double, {throw 1.1;})
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when DOUBLE exception is thrown", T4E_GET(p_double));
        TEST_FLAG(!ret); // expected: false
    }

    // TEST_TRUE
    {
        bool ret {true};
        test_true(ret, "Must be true", true);
        TEST_FLAG(ret)// expected: true
    }

    // TEST_FALSE
    {
        bool ret {true};
        test_false(ret, "Must be false", false);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        bool ret {true};
        test_eq(ret, "Must be same", 1, 1);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NE
    {
        bool ret {true};
        test_ne(ret, "Must not be equal", 2, 4);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GT
    {
        bool ret {true};
        test_gt(ret, "Must be greater than", 2, 1);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GE
    {
        bool ret {true};
        test_ge(ret, "Must be greater-or-equal", 2, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_LT
    {
        bool ret {true};
        test_lt(ret, "Must be lesser than", 1, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_LE
    {
        bool ret {true};
        test_le(ret, "Must be lesser-or-equal", 2, 2);
        TEST_FLAG(ret) // expected: true
    }

    return true;

}
