
#include "test_testforecho.h"

#include "testforecho.h"

#include <iostream>

bool test_testforecho(){

#define TEST_FLAG(BOOL_EXPR) if (!BOOL_EXPR) { std::cout << "Incorrect flag!" << std::endl; return false; }

    ///////////////////
    // BOOL NOT WRAPPED
    ///////////////////


    // TEST
    {
        auto comp = [](auto p1, auto p2) { return (p1 != p2); };
        bool ret {test("Must be different", 5, 6, comp)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EX
    {
        auto p = []() { throw 1; };
        bool ret {test_ex<int>("Must throw int", p)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        auto p = []() { throw 1; };
        bool ret {test_no_ex<double>("Must NOT throw double", p)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        auto p = []() { throw 'a'; };
        bool ret {test_any_ex("Must throw something", p)};
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_NO_EX
    {
        auto p = []() { /* i dont throw */ };
        bool ret {test_any_no_ex("Must not throw anything", p)};
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


    // TEST
    {
        bool ret {true};
        auto comp = [](auto p1, auto p2) { return (p1 == p2); };
        test(ret, "Must be same", 1, 1, comp);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EX
    {
        bool ret {true};
        auto p = []() { throw 1; };
        test_ex<int>(ret, "Must throw int", p);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        bool ret {true};
        auto p = []() { throw 1; };
        test_no_ex<double>(ret, "Must NOT throw double", p);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        bool ret {true};
        auto p = []() { /* i dont throw */ };
        test_any_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when no exception is thrown", p);
        TEST_FLAG(!ret) // expected: false
    }

    // TEST_ANY_NO_EX
    {
        bool ret {true};
        auto p_int = []() { throw 1; };
        auto p_double = []() { throw 1.1; };
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when INT exception is thrown", p_int);
        TEST_FLAG(!ret); // expected: false
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when DOUBLE exception is thrown", p_double);
        TEST_FLAG(!ret) // expected: false
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
