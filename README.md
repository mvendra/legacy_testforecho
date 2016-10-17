# testforecho
C++ unit testing micro-framework, lightweight, console based.

### integration
No linking or initialisation necessary, just include the headers and off you go (testforecho.h,
testforecho_internal.h and testforecho_compat.h).

testforecho uses generic lambdas (parameter auto), a C\+\+17 feature currently only present on GCC 5 as an extension. Clang 3.9.0, for example, lacks this feature. However, testforecho has a compatibility mode (testforecho_compat.h - not needed if your compiler has the C++ Concepts package)

To enable the compatibility mode, pass COMPILER_NO_CONCEPTS_SUPPORT to your compiler<br/>(-DCOMPILER_NO_CONCEPTS_SUPPORT)

### usage

Check the sample code (test_testforecho_first.cpp and test_testforecho_second.cpp), as they are rather self-explanatory.

The only tricky part is the compatibility interface (T4E_MAKE_0, T4E_MAKE_1, T4E_MAKE_2, ...) - their purpose is to create "predicates" with arbitrary code. The sample code include usage samples of these as well.

