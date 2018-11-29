# Makefile for dailyprogrammer

CFLAGS = -std=gnu++11 -Wall -O2
JAVAFLAGS = -Xlint

%.bin: %.cpp
	g++ -o $@ $^ $(CFLAGS)

%.class: %.java
	javac $^ $(JAVAFLAGS)

clean:
	rm -rf a *.exe *.class *.bin

# Run tests like this:
# make prog && time for item in tests/prog{TEST_CASES_HERE}.in ;do ./prog [optional args] < $item; done

# Maintaining a single Makefile for cleanliness
# from the year folder, run like:
# make -f ../Makefile challenge_n_difficulty && ./challenge_n_difficulty
