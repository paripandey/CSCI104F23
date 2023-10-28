CXX = g++
CPPFLAGS = -g -Wall -std=c++11 -Ilib

all: rsa

rsa: rsa.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf rsa