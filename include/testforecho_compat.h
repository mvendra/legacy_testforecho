
#ifndef __TESTFORECHO_COMPAT_H__
#define __TESTFORECHO_COMPAT_H__

#include <memory>

namespace testforecho {

struct subj_code {
    subj_code() {};
    virtual ~subj_code(){};
    subj_code(const subj_code&) = delete;
    subj_code(subj_code&&) = delete;
    subj_code& operator=(const subj_code&) = delete;
    subj_code& operator=(subj_code&&) = delete;
    virtual void run() = 0;
};

#define T4E_MAKE_0(A, ...) struct aux_class_##A : public subj_code { virtual void run() override { __VA_ARGS__ } };  std::unique_ptr<subj_code> A {std::make_unique<aux_class_##A>()};
#define T4E_MAKE_1(A, T1, V1, ...) struct aux_class_##A : public subj_code { T1 &V1; aux_class_##A(T1 &_V1):V1{_V1}{} virtual void run() override { __VA_ARGS__ } }; std::unique_ptr<subj_code> A {std::make_unique<aux_class_##A>(V1)};
#define T4E_MAKE_2(A, T1, V1, T2, V2, ...) struct aux_class_##A : public subj_code { T1 &V1; T2 &V2; aux_class_##A(T1 &_V1, T2 &_V2):V1{_V1}, V2{_V2}{} virtual void run() override { __VA_ARGS__ } }; std::unique_ptr<subj_code> A {std::make_unique<aux_class_##A>(V1, V2)};
#define T4E_GET(A) A.get()

// EXCEPTION TESTING

// Calls |testcase|
// Success: Exception of type |T| is thrown.
// Failures: Any other type of exception, or no exception is thrown.

template <typename T>
inline unsigned int test_ex(const std::string &msg, subj_code *testcase){
    try {
        testcase->run();
        FAIL(msg);
    } catch (const T& ex){ 
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

template <typename T>
inline unsigned int test_ex(subj_code *testcase){
    return test_ex<T>("", testcase);
}

// Calls |testcase|
// Success: A different type of exception than |T| is thrown, or no exception is thrown.
// Failures: Exception of type |T| is thrown.

template <typename T>
inline unsigned int test_no_ex(const std::string &msg, subj_code *testcase){
    try {
        testcase->run();
        PASS(msg);
    } catch (const T& ex){
        FAIL(msg);
    } catch (...){
        PASS(msg);
    }
}

template <typename T>
inline unsigned int test_no_ex(subj_code *testcase){
    return test_no_ex<T>("", testcase);
}

// Calls |testcase|
// Success: Any exception is thrown.
// Failures: No exception is thrown.

inline unsigned int test_any_ex(const std::string &msg, subj_code *testcase){
    try {
        testcase->run();
        FAIL(msg);
    } catch (...){ 
        PASS(msg);
    }
}

inline unsigned int test_any_ex(subj_code *testcase){
    return test_any_ex("", testcase);
}

// Calls |testcase|
// Success: No exception is thrown.
// Failures: Any exception is thrown.

inline unsigned int test_any_no_ex(const std::string &msg, subj_code *testcase){
    try {
        testcase->run();
        PASS(msg);
    } catch (...){
        FAIL(msg);
    }
}

inline unsigned int test_any_no_ex(subj_code *testcase){
    return test_any_no_ex("", testcase);
}

// HELPERS

template <typename X>
unsigned int test_true(const std::string &msg, X param){

    // reporting
    std::string t1 = handy_conversion(param);
    std::string t2 = handy_conversion(true);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param == true){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X>
unsigned int test_true(X param){
    return test_true("", param);
}

template <typename X>
unsigned int test_false(const std::string &msg, X param){

    // reporting
    std::string t1 = handy_conversion(param);
    std::string t2 = handy_conversion(false);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param == false){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X>
unsigned int test_false(X param){
    return test_false("", param);
}

template <typename X, typename Y>
unsigned int test_eq(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 == param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_eq(X param1, Y param2){
    return test_eq("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_neq(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 != param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_neq(X param1, Y param2){
    return test_neq("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_gt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 > param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_gt(X param1, Y param2){
    return test_gt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_ngt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (!(param1 > param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_ngt(X param1, Y param2){
    return test_ngt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_ge(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 >= param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_ge(X param1, Y param2){
    return test_ge("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nge(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (!(param1 >= param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_nge(X param1, Y param2){
    return test_nge("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_lt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 < param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_lt(X param1, Y param2){
    return test_lt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nlt(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (!(param1 < param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_nlt(X param1, Y param2){
    return test_nlt("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_le(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (param1 <= param2){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_le(X param1, Y param2){
    return test_le("", param1, param2);
}

template <typename X, typename Y>
unsigned int test_nle(const std::string &msg, X param1, Y param2){

    // reporting
    std::string t1 = handy_conversion(param1);
    std::string t2 = handy_conversion(param2);
    std::string msg_plus_params;
    if (msg == ""){ msg_plus_params = "(" + t1 + ", " + t2 + ")"; }
    else { msg_plus_params = msg + " (" + t1 + ", " + t2 + ")"; }

    // testing
    if (!(param1 <= param2)){ PASS(msg_plus_params); }
    else { FAIL(msg_plus_params); }

}

template <typename X, typename Y>
unsigned int test_nle(X param1, Y param2){
    return test_nle("", param1, param2);
}

// INTERFACE EXTENSIONS

template <typename T>
inline void test_ex(unsigned int &total, const std::string &msg, subj_code *testcase){
    total += test_ex<T>(msg, testcase);
}

template <typename T>
inline void test_ex(unsigned int &total, subj_code *testcase){
    total += test_ex<T>(testcase);
}

template <typename T>
inline void test_no_ex(unsigned int &total, const std::string &msg, subj_code *testcase){
    total += test_no_ex<T>(msg, testcase);
}

template <typename T>
inline void test_no_ex(unsigned int &total, subj_code *testcase){
    total += test_no_ex<T>(testcase);
}

inline void test_any_ex(unsigned int &total, const std::string &msg, subj_code *testcase){
    total += test_any_ex(msg, testcase);
}

inline void test_any_ex(unsigned int &total, subj_code *testcase){
    total += test_any_ex(testcase);
}

inline void test_any_no_ex(unsigned int &total, const std::string &msg, subj_code *testcase){
    total += test_any_no_ex(msg, testcase);
}

inline void test_any_no_ex(unsigned int &total, subj_code *testcase){
    total += test_any_no_ex(testcase);
}

template <typename X>
void test_true(unsigned int &total, const std::string &msg, X param){
    total += test_true<X>(msg, param);
}

template <typename X>
void test_true(unsigned int &total, X param){
    total += test_true<X>("", param);
}

template <typename X>
void test_false(unsigned int &total, const std::string &msg, X param){
    total += test_false<X>(msg, param);
}

template <typename X>
void test_false(unsigned int &total, X param){
    total += test_false<X>("", param);
}

template <typename X, typename Y>
void test_eq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_eq(unsigned int &total, X param1, Y param2){
    total += test_eq<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_neq(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_neq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_neq(unsigned int &total, X param1, Y param2){
    total += test_neq<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_gt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(unsigned int &total, X param1, Y param2){
    total += test_gt<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_ngt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_ngt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ngt(unsigned int &total, X param1, Y param2){
    total += test_ngt<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_ge(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(unsigned int &total, X param1, Y param2){
    total += test_ge<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_nge(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nge(unsigned int &total, X param1, Y param2){
    total += test_nge<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_lt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(unsigned int &total, X param1, Y param2){
    total += test_lt<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_nlt(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nlt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nlt(unsigned int &total, X param1, Y param2){
    total += test_nlt<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_le(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_le<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(unsigned int &total, X param1, Y param2){
    total += test_le<X, Y>("", param1, param2);
}

template <typename X, typename Y>
void test_nle(unsigned int &total, const std::string &msg, X param1, Y param2){
    total += test_nle<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_nle(unsigned int &total, X param1, Y param2){
    total += test_nle<X, Y>("", param1, param2);
}

} // ns: testforecho

#endif //__TESTFORECHO_COMPAT_H__
