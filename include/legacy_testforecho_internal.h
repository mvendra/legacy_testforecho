
#ifndef __TESTFORECHO_INTERNAL_H__
#define __TESTFORECHO_INTERNAL_H__

// THE PRAGMA BELOW IS TO ALLOW THE USE OF AUTO AS A FUNCTION PARAMETER
#ifdef __GNUC__
#pragma GCC system_header // disabling error-triggering warnings
#endif

namespace legacy_testforecho {

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
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (func(param1, param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test(X param1, Y param2, auto func){
    return test<X, Y>("", param1, param2, func);
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

template <typename T>
unsigned int test_ex(auto testcase){
    return test_ex<T>("", testcase);
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

template <typename T>
unsigned int test_no_ex(auto testcase){
    return test_no_ex<T>("", testcase);
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

unsigned int test_any_ex(auto testcase){
    return test_any_ex("", testcase);
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

unsigned int test_any_no_ex(auto testcase){
    return test_any_no_ex("", testcase);
}

// HELPERS

template <typename X>
unsigned int test_true(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, true, comp_eq);
}

template <typename X>
unsigned int test_true(X param){
    return test_true("", param);
}

template <typename X>
unsigned int test_false(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, false, comp_eq);
}

template <typename X>
unsigned int test_false(X param){
    return test_false("", param);
}

template <typename X, typename Y>
unsigned int test_eq(const std::string &msg, X param1, Y param2){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param1, param2, comp_eq);
}

template <typename X, typename Y>
unsigned int test_eq(X param1, Y param2){
    return test_eq("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_neq(const std::string &msg, X param1, Y param2){
    auto comp_neq = [](auto p1, auto p2) { return (p1 != p2); };
    return test(msg, param1, param2, comp_neq);
}

template <typename X, typename Y>
unsigned int test_neq(X param1, Y param2){
    return test_neq("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_gt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 > p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
unsigned int test_gt(X param1, Y param2){
    return test_gt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_ngt(const std::string &msg, X param1, Y param2){
    auto comp_ngt = [](auto p1, auto p2) { return (!(p1 > p2)); };
    return test(msg, param1, param2, comp_ngt);
}

template <typename X, typename Y>
unsigned int test_ngt(X param1, Y param2){
    return test_ngt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_ge(const std::string &msg, X param1, Y param2){
    auto comp_ge = [](auto p1, auto p2) { return (p1 >= p2); };
    return test(msg, param1, param2, comp_ge);
}

template <typename X, typename Y>
unsigned int test_ge(X param1, Y param2){
    return test_ge("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nge(const std::string &msg, X param1, Y param2){
    auto comp_nge = [](auto p1, auto p2) { return (!(p1 >= p2)); };
    return test(msg, param1, param2, comp_nge);
}

template <typename X, typename Y>
unsigned int test_nge(X param1, Y param2){
    return test_nge("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_lt(const std::string &msg, X param1, Y param2){
    auto comp_lt = [](auto p1, auto p2) { return (p1 < p2); };
    return test(msg, param1, param2, comp_lt);
}

template <typename X, typename Y>
unsigned int test_lt(X param1, Y param2){
    return test_lt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nlt(const std::string &msg, X param1, Y param2){
    auto comp_nlt = [](auto p1, auto p2) { return (!(p1 < p2)); };
    return test(msg, param1, param2, comp_nlt);
}

template <typename X, typename Y>
unsigned int test_nlt(X param1, Y param2){
    return test_nlt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_le(const std::string &msg, X param1, Y param2){
    auto comp_le = [](auto p1, auto p2) { return (p1 <= p2); };
    return test(msg, param1, param2, comp_le);
}

template <typename X, typename Y>
unsigned int test_le(X param1, Y param2){
    return test_le("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nle(const std::string &msg, X param1, Y param2){
    auto comp_nle = [](auto p1, auto p2) { return (!(p1 <= p2)); };
    return test(msg, param1, param2, comp_nle);
}

template <typename X, typename Y>
unsigned int test_nle(X param1, Y param2){
    return test_nle("", param1, param2);
}

// INTERFACE EXTENSIONS

template <typename X, typename Y>
void test(unsigned int &total, const std::string &msg, X param1, Y param2, auto func){
    total += test<X, Y>(msg, param1, param2, func);
}

template <typename X, typename Y>
void test(unsigned int &total, X param1, Y param2, auto func){
    total += test<X, Y>(param1, param2, func);
}

template <typename T>
void test_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_ex<T>(msg, testcase);
}

template <typename T>
void test_ex(unsigned int &total, auto testcase){
    total += test_ex<T>(testcase);
}

template <typename T>
void test_no_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_no_ex<T>(msg, testcase);
}

template <typename T>
void test_no_ex(unsigned int &total, auto testcase){
    total += test_no_ex<T>(testcase);
}

void test_any_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_any_ex(msg, testcase);
}

void test_any_ex(unsigned int &total, auto testcase){
    total += test_any_ex(testcase);
}

void test_any_no_ex(unsigned int &total, const std::string &msg, auto testcase){
    total += test_any_no_ex(msg, testcase);
}

void test_any_no_ex(unsigned int &total, auto testcase){
    total += test_any_no_ex(testcase);
}

template <typename X>
void test_true(unsigned int &total, const std::string &msg, X param){
    total += test_true<X>(msg, param);
}

template <typename X>
void test_true(unsigned int &total, X param){
    total += test_true<X>(param);
}

template <typename X>
void test_false(unsigned int &total, const std::string &msg, X param){
    total += test_false<X>(msg, param);
}

template <typename X>
void test_false(unsigned int &total, X param){
    total += test_false<X>(param);
}

template <typename X, typename Y>
void test_eq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_eq(unsigned int &total, X param1, Y param2){
    total += test_eq<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_neq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_neq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_neq(unsigned int &total, X param1, Y param2){
    total += test_neq<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_gt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(unsigned int &total, X param1, Y param2){
    total += test_gt<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_ngt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_ngt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ngt(unsigned int &total, X param1, Y param2){
    total += test_ngt<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_ge(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(unsigned int &total, X param1, Y param2){
    total += test_ge<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_nge(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nge(unsigned int &total, X param1, Y param2){
    total += test_nge<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_lt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(unsigned int &total, X param1, Y param2){
    total += test_lt<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_nlt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nlt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nlt(unsigned int &total, X param1, Y param2){
    total += test_nlt<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_le(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_le<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(unsigned int &total, X param1, Y param2){
    total += test_le<X, Y>(param1, param2);
}

template <typename X, typename Y>
void test_nle(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nle<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nle(unsigned int &total, X param1, Y param2){
    total += test_nle<X, Y>(param1, param2);
}

} // ns: legacy_testforecho

#endif // __LEGACY_TESTFORECHO_INTERNAL_H__
