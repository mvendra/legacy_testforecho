
#ifndef __TESTFORECHO_INTERNAL_H__
#define __TESTFORECHO_INTERNAL_H__

// THE PRAGMA BELOW IS TO ALLOW THE USE OF AUTO AS A FUNCTION PARAMETER
#ifdef __GNUC__
#pragma GCC system_header // disabling error-triggering warnings
#endif

namespace testforecho {

#define T4E_MAKE_0(A, ...) auto A = []() { __VA_ARGS__ };
#define T4E_MAKE_1(A, T1, V1, ...) auto A = [&V1]() { __VA_ARGS__ };
#define T4E_MAKE_2(A, T1, V1, T2, V2, ...) auto A = [&V1, &V2]() { __VA_ARGS__ };
#define T4E_GET(A) A

// BASIC TESTING

// Calls |func| with |param1| and |param2|
// Success: |func| returns true
// Failure: |func| returns false

template <typename X, typename Y>
unsigned int test(const std::string &msg, X param1, Y param2, auto func){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params = msg + " (" + t1 + ", " + t2 + ")";

    // testing
    if (func(param1, param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

// EXCEPTION TESTING

// Calls |testcase|
// Success: Exception of type |T| is thrown.
// Failures: Any other type of exception, or no exception is thrown.

template <typename T>
unsigned int test_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        FAIL(msg);
    } catch (const T& ex){ 
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

// Calls |testcase|
// Success: A different type of exception than |T| is thrown, or no exception is thrown.
// Failures: Exception of type |T| is thrown.

template <typename T>
unsigned int test_no_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        PASS(msg);
    } catch (const T& ex){
        FAIL(msg);
    } catch (...){
        PASS(msg);
    }
}

// Calls |testcase|
// Success: Any exception is thrown.
// Failures: No exception is thrown.

unsigned int test_any_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        FAIL(msg);
    } catch (...){ 
        PASS(msg);
    }
}

// Calls |testcase|
// Success: No exception is thrown.
// Failures: Any exception is thrown.

unsigned int test_any_no_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

// HELPERS

template <typename X>
unsigned int test_nullptr(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, nullptr, comp_eq);
}

template <typename X>
unsigned int test_true(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, true, comp_eq);
}

template <typename X>
unsigned int test_false(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, false, comp_eq);
}

template <typename X, typename Y>
unsigned int test_eq(const std::string &msg, X param1, Y param2){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param1, param2, comp_eq);
}

template <typename X, typename Y>
unsigned int test_neq(const std::string &msg, X param1, Y param2){
    auto comp_ne = [](auto p1, auto p2) { return (p1 != p2); };
    return test(msg, param1, param2, comp_ne);
}

template <typename X, typename Y>
unsigned int test_gt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 > p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
unsigned int test_ge(const std::string &msg, X param1, Y param2){
    auto comp_ge = [](auto p1, auto p2) { return (p1 >= p2); };
    return test(msg, param1, param2, comp_ge);
}

template <typename X, typename Y>
unsigned int test_lt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 < p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
unsigned int test_le(const std::string &msg, X param1, Y param2){
    auto comp_le = [](auto p1, auto p2) { return (p1 <= p2); };
    return test(msg, param1, param2, comp_le);
}

// INTERFACE EXTENSIONS

template <typename X, typename Y>
void test(unsigned int &total, const std::string &msg, X param1, Y param2, auto func){
    total += test<X, Y>(msg, param1, param2, func);
}

template <typename T>
void test_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_ex<T>(msg, testcase);
}

template <typename T>
void test_no_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_no_ex<T>(msg, testcase);
}

void test_any_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_any_ex(msg, testcase);
}

void test_any_no_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_any_no_ex(msg, testcase);
}

template <typename X>
void test_nullptr(unsigned int &total, const std::string &msg, X param){
    total += test_nullptr<X>(msg, param);
}

template <typename X>
void test_true(unsigned int &total, const std::string &msg, X param){
    total += test_true<X>(msg, param);
}

template <typename X>
void test_false(unsigned int &total, const std::string &msg, X param){
    total += test_false<X>(msg, param);
}

template <typename X, typename Y>
void test_eq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_neq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_neq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_le<X, Y>(msg, param1, param2);
}

} // ns: testforecho

#endif // __TESTFORECHO_INTERNAL_H__
