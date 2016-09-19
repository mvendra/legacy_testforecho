
#ifndef __TESTFORECHO_H__
#define __TESTFORECHO_H__

#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo> // for pretty printing bool

#define COLOR_WHITE  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"

#define PRINT_ERROR(MSG) std::cout << COLOR_RED << MSG << COLOR_WHITE << std::endl;
#define PRINT_SUCCESS(MSG) std::cout << COLOR_GREEN << MSG << COLOR_WHITE << std::endl;
#define PRINT_INFO(MSG) std::cout << COLOR_WHITE << MSG << std::endl;

#define PASS(MSG) PRINT_SUCCESS("Passed: " + MSG); return true;
#define FAIL(MSG) PRINT_ERROR("FAILED: " + MSG); return false;

// THE PRAGMA BELOW IS TO ALLOW THE USE OF AUTO AS A FUNCTION PARAMETER
#ifdef __GNUC__
#pragma GCC system_header // disabling error-triggering warnings
#endif

// BASIC TESTING

// Calls |func| with |param1| and |param2|
// Success: |func| returns true
// Failure: |func| returns false

template <typename T>
std::string handy_conversion(T val){
    std::stringstream ss;
    if (typeid(T) == typeid(bool)){
        ss << std::boolalpha;
    }
    ss << val;
    return ss.str(); 
}

template <typename X, typename Y>
bool test(const std::string &msg, X param1, Y param2, auto func){

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
bool test_ex(const std::string &msg, auto testcase){
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
bool test_no_ex(const std::string &msg, auto testcase){
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

bool test_any_ex(const std::string &msg, auto testcase){
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

bool test_any_no_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

// HELPERS

template <typename X>
bool test_true(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, true, comp_eq);
}

template <typename X>
bool test_false(const std::string &msg, X param){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param, false, comp_eq);
}

template <typename X, typename Y>
bool test_eq(const std::string &msg, X param1, Y param2){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param1, param2, comp_eq);
}

template <typename X, typename Y>
bool test_ne(const std::string &msg, X param1, Y param2){
    auto comp_ne = [](auto p1, auto p2) { return (p1 != p2); };
    return test(msg, param1, param2, comp_ne);
}

template <typename X, typename Y>
bool test_gt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 > p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
bool test_ge(const std::string &msg, X param1, Y param2){
    auto comp_ge = [](auto p1, auto p2) { return (p1 >= p2); };
    return test(msg, param1, param2, comp_ge);
}

template <typename X, typename Y>
bool test_lt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 < p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
bool test_le(const std::string &msg, X param1, Y param2){
    auto comp_le = [](auto p1, auto p2) { return (p1 <= p2); };
    return test(msg, param1, param2, comp_le);
}

// INTERFACE EXTENSIONS

template <typename X, typename Y>
void test(bool &total, const std::string &msg, X param1, Y param2, auto func){
    total &= test<X, Y>(msg, param1, param2, func);
}

template <typename T>
void test_ex(bool &total, const std::string &msg, auto testcase){
    total &= test_ex<T>(msg, testcase);
}

template <typename T>
void test_no_ex(bool &total, const std::string &msg, auto testcase){
    total &= test_no_ex<T>(msg, testcase);
}

void test_any_ex(bool &total, const std::string &msg, auto testcase){
    total &= test_any_ex(msg, testcase);
}

void test_any_no_ex(bool &total, const std::string &msg, auto testcase){
    total &= test_any_no_ex(msg, testcase);
}

template <typename X>
void test_true(bool &total, const std::string &msg, X param){
    total &= test_true<X>(msg, param);
}

template <typename X>
void test_false(bool &total, const std::string &msg, X param){
    total &= test_false<X>(msg, param);
}

template <typename X, typename Y>
void test_eq(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ne(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ne<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_le<X, Y>(msg, param1, param2);
}

#endif // __TESTFORECHO_H__
