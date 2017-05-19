# Makefile for dailyprogrammer

CFLAGS = -std=gnu++11 -Wall -O2

%: %.cpp
	g++ -o a $^ $(CFLAGS)
	
clean:
	rm -f a a.exe* a.out
	
	
# Run tests like this:
# make 12-05_294_Easy && time for item in tests/12-05_Easy_294_{TEST_CASES_HERE}.in ;do ./a [optional args] < $item; done