# legacy_testforecho
C++ unit testing micro-framework, lightweight, console based.

### integration
No linking or initialization necessary, just include the headers and off you go (legacy_testforecho.h,
legacy_testforecho_internal.h and legacy_testforecho_compat.h).


### compiler support
GCC 5 works "out of the box".
LLVM 3.9 and MSVC14 (VS 2015) also work, when using legacy_testforecho in compatibility mode (see below)

legacy_testforecho uses generic lambdas (parameter auto), a C\+\+17 feature currently only present on GCC 5 as an extension. Clang 3.9.0, for example, lacks this feature. However, legacy_testforecho has a compatibility mode (legacy_testforecho_compat.h - not needed if your compiler has the C++ Concepts package)

To enable the compatibility mode, pass COMPILER_NO_CONCEPTS_SUPPORT to your compiler<br/>(-DCOMPILER_NO_CONCEPTS_SUPPORT)

### usage

Quick example:
```c
#include "legacy_testforecho.h" // this requires -I./legacy_testforecho/include
using namespace legacy_testforecho;

unsigned int errors {0};

int x {5}; int y {5};
test_eq(errors, "X and Y must match", x, y);

bool flag {true};
test_true(errors, "Flag must be true", flag);

T4E_MAKE_0(predicate, {DateHelper dh{7, 80, 1978};} ) // invalid date
test_ex<Ex_Invalid_Date>(errors, "Should raise exception", T4E_GET(predicate));
```

Check the sample code (test_legacy_testforecho_first.cpp and test_legacy_testforecho_second.cpp) for fuller examples, they are rather self-explanatory.

The only tricky part is the compatibility interface (T4E_MAKE_0, T4E_MAKE_1, T4E_MAKE_2, ...) - their purpose is to create "predicates" with arbitrary code. The sample code include usage samples of these as well.

