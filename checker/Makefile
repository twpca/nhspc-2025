CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff float_diff float_diff_inf test3 test4 test5_manager test6_manager

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff

float_diff: float_diff.cpp
	$(CC) float_diff.cpp $(CCARGS) -o float_diff

float_diff_inf: float_diff_inf.cpp
	$(CC) float_diff_inf.cpp $(CCARGS) -o float_diff_inf

test3: test3.cpp
	$(CC) test3.cpp $(CCARGS) -o test3

test4: test4.cpp
	$(CC) test4.cpp $(CCARGS) -o test4

test5_manager: test5_manager.cpp
	$(CC) test5_manager.cpp $(CCARGS) -o test5_manager

test6_manager: test6_manager.cpp
	$(CC) test6_manager.cpp $(CCARGS) -o test6_manager
