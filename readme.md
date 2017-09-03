Yet Another Circular Buffer
===========================

[![Build Status](https://travis-ci.org/cjhdev/circular_buffer.svg?branch=master)](https://travis-ci.org/cjhdev/circular_buffer)

- I am using C in an OO style so it is possible to have more than one instance
- My interface names line up with the requirements but these are probably too generic for practical use
- Buffer capacity is a compile time setting that defaults to 42 elements
    - Redefine at compile time like this `-DCIRCULAR_BUFFER_SIZE=123`
- I am using Cmocka to exercise the code
- C source files are in `/src`
    - [circular_buffer.c](src/circular_buffer.c)
- C header files are in `/include`
    - [circular_buffer.h](include/circular_buffer.h)
- Test files are in `/test`
    - [tc_circular_buffer.c](test/tc_circular_buffer.c)
    - [makefile](test/makefile)
- Source has been linted with PCLINT usinng the configuration contained within `/pclint`

## Running the Tests

You need:

- GCC
- Make
- Gcov (if you want a coverage report)

From project root:

~~~
cd test
make
cd -
~~~

To see test coverage:

~~~
cd test
make coverage
cd -
~~~

## License

Yet Another Circular Buffer has an MIT license.
