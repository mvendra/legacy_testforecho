
#ifndef __TESTFORECHO_H__
#define __TESTFORECHO_H__

#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo> // for typeid()

namespace testforecho {

#ifndef NDEBUG // debug mode
#define PRIVATE public
#else
#define PRIVATE private
#endif

#define COLOR_WHITE  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"

#define PRINT_ERROR(MSG) std::cout << COLOR_RED << MSG << COLOR_WHITE << std::endl;
#define PRINT_SUCCESS(MSG) std::cout << COLOR_GREEN << MSG << COLOR_WHITE << std::endl;
#define PRINT_INFO(MSG) std::cout << COLOR_WHITE << MSG << std::endl;

#define PASS(MSG) PRINT_SUCCESS( (MSG == "" ? "Passed." : "Passed: " + MSG) ); return 0;
#define FAIL(MSG) PRINT_ERROR  ( (MSG == "" ? "FAILED." : "FAILED: " + MSG) ); return 1;

template <typename T>
std::string handy_conversion(T val){
    std::stringstream ss;
    if (typeid(T) == typeid(bool)){
        ss << std::boolalpha;
    }
    ss << val;
    return ss.str(); 
}

} // ns: testforecho

#ifndef COMPILER_NO_CONCEPTS_SUPPORT
#include "testforecho_internal.h"
#else
#include "testforecho_compat.h"
#endif // COMPILER_NO_CONCEPTS_SUPPORT

#endif // __TESTFORECHO_H__
