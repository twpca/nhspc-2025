CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
GENERATOR_LIST = test \
				 postoffice \
				 parade \
				 diameter \
				 connections

all: $(GENERATOR_LIST)

clean:
	rm -f $(GENERATOR_LIST)

test: test.cpp
	$(CC) test.cpp $(CCARGS) -o test

run_test: test
	./test 100 1
	./test 200 2

ev: ev.cpp
	$(CC) ev.cpp $(CCARGS) -o ev

run_ev: ev
	./ev 1
	./ev 2
	./ev 3
	./ev 4

-include connections.mk

postoffice: postoffice.cpp
	$(CC) postoffice.cpp $(CCARGS) -o postoffice

run_postoffice: postoffice
	./postoffice 1 1000 0 1 1000000000 
	./postoffice 2 1000 1000 1000 1000000000 
	./postoffice 3 100000 0 100000 1000000 
	./postoffice 4 100000 100000 100000 1000000 
	./postoffice 5 1000000 1000000 1000000 1000000000

brackets: brackets.cpp
	$(CC) brackets.cpp $(CCARGS) -o brackets.exe

run_brackets: brackets
	./brackets.exe

decode: decode.cpp
	$(CC) decode.cpp $(CCARGS) -o decode

run_decode: decode
	./decode 1 1000000 6 1000000 1000000
	./decode 2 10 2 1000000000 0
	./decode 3 100000 6 1000000000 0
	./decode 4 1000000000 6 1000000000 0


-include datacenter.mk

-include parade.mk

-include diameter.mk

-include chomp.mk