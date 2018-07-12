Some information from me to future me

# About
My solutions/attempts at /r/dailyprogrammer problems. Each attempt may or may not include test cases (where applicable). These might be internal tests (e.g. assertions or lbTest functions in the file) or external tests (e.g. files to use as input/output).

# Directory Structure
```
Makefile, helpers.cpp, lbTest.h
dailyprogrammer/year/
dailyprogrammer/year/tests/
```

The single Makefile can be used across all the `year` folders. Invoke with `make -f ../Makefile target` from the `year` folder

Within each folder, each file is like this:
```
Solution: year/challenge_n_difficulty.fileExtension
Test case (INPUT): challenge_n_difficulty_TESTID.in
Test case (OUTPUT): challenge_n_difficulty_TESTID.out // where TESTID matches the TESTID of its input
```

"challenge" is included as a prefix to allow (for example) Java files to have a class name identical to the file name.

A handy regex for mass-renaming from `DD-MM_N_difficulty...` if necessary:
```bash
for item in *.* ;do git mv "$item" "$(echo "$item" | sed "s/[0-9]\+-[0-9]\+_\([0-9]\+_[a-zA-Z]\+.*\)/challenge_\1/" | awk '{print tolower($0)}')"; done
```

NOTE: Some of the in/outputs will be handled by `lbTest` where applicable (e.g. comparing a simple string input to a string output, etc. )

As of yet, I have no way of signifying that a thing is being handled by `lbTest`, or even whether it has tests associated with it.
