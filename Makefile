GTEST_INC_PATH ?= /usr/local/include/
GTEST_LIB_PATH ?= /usr/local/lib/

test: tradebook.t.cpp tradebook.cpp
	g++ -o test_tradebook -std=gnu++11 -I. -I$(GTEST_INC_PATH) -L$(GTEST_LIB_PATH) -lgtest tradebook.t.cpp tradebook.cpp

main: main.m.cpp tradebook.cpp
	g++ -o tradebook -std=gnu++11 -I. main.m.cpp tradebook.cpp