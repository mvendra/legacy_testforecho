
#include "test_legacy_testforecho_first.h"

#include "legacy_testforecho.h"

using namespace legacy_testforecho;

unsigned int test_legacy_testforecho_first(){

#define TEST_FLAG(EXPR) if ((EXPR) > 0) { std::cout << "Incorrect flag!" << std::endl; return 1; }

    #ifdef COMPILER_NO_CONCEPTS_SUPPORT
    PRINT_INFO("Using legacy_testforecho in compatibility mode (no param auto)")
    #endif

    ///////////////////
    // UNSIGNED INT NOT WRAPPED
    ///////////////////

    #ifndef COMPILER_NO_CONCEPTS_SUPPORT
    // TEST
    {
        auto comp = [](auto p1, auto p2) { return (p1 != p2); };
        unsigned int ret {test("Must be different", 5, 6, comp)};
        TEST_FLAG(ret) // expected: true
        ret = test(5, 6, comp);
        TEST_FLAG(ret) // expected: true
    }
    #endif // COMPILER_NO_CONCEPTS_SUPPORT

    // TEST_EX
    {
        T4E_MAKE_0(p, {throw 1;})
        unsigned int ret {test_ex<int>("Must throw int", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
        ret = test_ex<int>(T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        T4E_MAKE_0(p, {throw 1;})
        unsigned int ret {test_no_ex<double>("Must NOT throw double", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
        ret = test_no_ex<double>(T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        T4E_MAKE_0(p, {throw 'a';})
        unsigned int ret {test_any_ex("Must throw something", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
        ret = test_any_ex(T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_NO_EX
    {
        T4E_MAKE_0(p, {/* i dont throw */})
        unsigned int ret {test_any_no_ex("Must not throw anything", T4E_GET(p))};
        TEST_FLAG(ret) // expected: true
        ret = test_any_no_ex(T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_TRUE
    {
        unsigned int ret {test_true("Must be true", !false)};
        TEST_FLAG(ret) // expected: true
        ret = test_true(!false);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_FALSE
    {
        unsigned int ret {test_false("Must be false", !true)};
        TEST_FLAG(ret) // expected: true
        ret = test_false(!true);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        unsigned int ret {test_eq("Must be equal", 1, 1)};
        TEST_FLAG(ret) // expected: true
        ret = test_eq(1, 1);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NEQ
    {
        unsigned int ret {test_neq("Must not be equal", 'p', 57)};
        TEST_FLAG(ret) // expected: true
        ret = test_neq('p', 57);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GT
    {
        unsigned int ret {test_gt("Must be greater than", 30, 20)};
        TEST_FLAG(ret) // expected: true
        ret = test_gt(30, 20);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NGT
    {
        unsigned int ret {test_ngt("Must not be greater than", 20, 21)};
        TEST_FLAG(ret) // expected: true
        ret = test_ngt(20, 21);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GE
    {
        unsigned int ret {test_ge("Must be greater-or-equal", 10, 10)};
        TEST_FLAG(ret) // expected: true
        ret = test_ge(10, 10);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NGE
    {
        unsigned int ret {test_nge("Must not be greater-or-equal", 9, 10)};
        TEST_FLAG(ret) // expected: true
        ret = test_nge(9, 10);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_LT
    {
        unsigned int ret {test_lt("Must be lesser than", 30, 80)};
        TEST_FLAG(ret);
        ret = test_lt(30, 80);
        TEST_FLAG(ret);
    }

    // TEST_NLT
    {
        unsigned int ret {test_nlt("Must not be lesser than", 300, 300)};
        TEST_FLAG(ret);
        ret = test_nlt(300, 300);
        TEST_FLAG(ret);
    }

    // TEST_LE
    {
        unsigned int ret {test_le("Must be lesser-or-equal", 9, 9)};
        TEST_FLAG(ret);
        ret = test_le(9, 9);
        TEST_FLAG(ret);
    }

    // TEST_NLE
    {
        unsigned int ret {test_nle("Must not be lesser-or-equal", 10, 8)};
        TEST_FLAG(ret);
        ret = test_nle(10, 8);
        TEST_FLAG(ret);
    }

    ///////////////
    // UNSIGNED INT WRAPPED
    ///////////////

    #ifndef COMPILER_NO_CONCEPTS_SUPPORT
    // TEST
    {
        unsigned int ret {0};
        auto comp = [](auto p1, auto p2) { return (p1 == p2); };
        test(ret, "Must be same", 1, 1, comp);
        TEST_FLAG(ret) // expected: true
        test(ret, 1, 1, comp);
        TEST_FLAG(ret) // expected: true
    }
    #endif // COMPILER_NO_CONCEPTS_SUPPORT

    // TEST_EX
    {
        unsigned int ret {0};
        T4E_MAKE_0(p, {throw 1;})
        test_ex<int>(ret, "Must throw int", T4E_GET(p));
        TEST_FLAG(ret) // expected: true
        test_ex<int>(ret, T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NO_EX
    {
        unsigned int ret {0};
        T4E_MAKE_0(p, {throw 1;})
        test_no_ex<double>(ret, "Must NOT throw double", T4E_GET(p));
        TEST_FLAG(ret) // expected: true
        test_no_ex<double>(ret, T4E_GET(p));
        TEST_FLAG(ret) // expected: true
    }

    // TEST_ANY_EX
    {
        unsigned int ret {0};
        T4E_MAKE_0(p, {/* i dont throw */})
        test_any_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when no exception is thrown", T4E_GET(p));
        TEST_FLAG(!ret) // expected: false
        PRINT_INFO("If the following message fails, it's a success:")
        test_any_ex(ret, T4E_GET(p));
        TEST_FLAG(!ret) // expected: false
    }

    // TEST_ANY_NO_EX
    {
        unsigned int ret {0};
        T4E_MAKE_0(p_int, {throw 1;})
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when INT exception is thrown", T4E_GET(p_int));
        TEST_FLAG(!ret); // expected: false
        PRINT_INFO("If the following message fails, it's a success:")
        test_any_no_ex(ret, T4E_GET(p_int));
        TEST_FLAG(!ret); // expected: false
        T4E_MAKE_0(p_double, {throw 1.1;})
        test_any_no_ex(ret, "IF THIS FAILS, IT'S A SUCCESS! Should fail when DOUBLE exception is thrown", T4E_GET(p_double));
        PRINT_INFO("If the following message fails, it's a success:")
        test_any_no_ex(ret, T4E_GET(p_double));
        TEST_FLAG(!ret); // expected: false
    }

    // TEST_TRUE
    {
        unsigned int ret {0};
        test_true(ret, "Must be true", true);
        TEST_FLAG(ret)// expected: true
        test_true(ret, true);
        TEST_FLAG(ret)// expected: true
    }

    // TEST_FALSE
    {
        unsigned int ret {0};
        test_false(ret, "Must be false", false);
        TEST_FLAG(ret) // expected: true
        test_false(ret, false);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_EQ
    {
        unsigned int ret {0};
        test_eq(ret, "Must be same", 1, 1);
        TEST_FLAG(ret) // expected: true
        test_eq(ret, 1, 1);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NEQ
    {
        unsigned int ret {0};
        test_neq(ret, "Must not be equal", 2, 4);
        TEST_FLAG(ret) // expected: true
        test_neq(ret, 2, 4);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GT
    {
        unsigned int ret {0};
        test_gt(ret, "Must be greater than", 2, 1);
        TEST_FLAG(ret) // expected: true
        test_gt(ret, 2, 1);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NGT
    {
        unsigned int ret {0};
        test_ngt(ret, "Must not be greater than", 2, 2);
        TEST_FLAG(ret) // expected: true
        test_ngt(ret, 2, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_GE
    {
        unsigned int ret {0};
        test_ge(ret, "Must be greater-or-equal", 2, 2);
        TEST_FLAG(ret) // expected: true
        test_ge(ret, 2, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NGE
    {
        unsigned int ret {0};
        test_nge(ret, "Must not be greater-or-equal", 1, 2);
        TEST_FLAG(ret) // expected: true
        test_nge(ret, 1, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_LT
    {
        unsigned int ret {0};
        test_lt(ret, "Must be lesser than", 1, 2);
        TEST_FLAG(ret) // expected: true
        test_lt(ret, 1, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NLT
    {
        unsigned int ret {0};
        test_nlt(ret, "Must not be lesser than", 2, 2);
        TEST_FLAG(ret) // expected: true
        test_nlt(ret, 2, 2);
        TEST_FLAG(ret) // expected: true 
    }

    // TEST_LE
    {
        unsigned int ret {0};
        test_le(ret, "Must be lesser-or-equal", 2, 2);
        TEST_FLAG(ret) // expected: true
        test_le(ret, 2, 2);
        TEST_FLAG(ret) // expected: true
    }

    // TEST_NLE
    {
        unsigned int ret {0};
        test_nle(ret, "Must not be lesser-or-equal", 3, 2);
        TEST_FLAG(ret) // expected: true
        test_nle(ret, 3, 2);
        TEST_FLAG(ret) // expected: true
    }

    return 0;

}
