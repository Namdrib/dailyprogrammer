# Makefile for dailyprogrammer

CFLAGS = -std=gnu++11 -Wall -O2
JAVAFLAGS = -Xlint

%: %.cpp
	g++ -o $@ $^ $(CFLAGS)

%: %.java
	javac $^ $(JAVAFLAGS)
	
clean:
	rm -f a a.exe* a.out
	
	
# Run tests like this:
# make 12-05_294_Easy && time for item in tests/12-05_Easy_294_{TEST_CASES_HERE}.in ;do ./a [optional args] < $item; done

# Maintaining a single Makefile for cleanliness
# from the year folder, run like:
# make -f ../Makefile challenge_n_difficulty && ./challenge_n_difficulty
