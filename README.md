# trades-summary

C++ TDD example with trade summary program

### How to use

* To build gtest,
```
make test
```
Make sure gtest headers are available in $GTEST_INC_PATH, and gtest library is available in $GTEST_LIB_PATH.

* To build main,
```
make main
```

### What to expect

* gtest: 16 passing cases covering public functions of tradebook.
* main: given input.csv, write output.csv with summary. input.csv is assumed to be present in current directory, and its content is well-formed. main does not write to std::cout or std::cerr.