Some information from me to future me

Directory structure is as follows:
```
dailyprogrammer/year/
dailyprogrammer/year/tests/
dailyprogrammer/year/Makefile (file) -> Used to `make clean`
```

Within each folder, each file is like this:
```
Solution: year/challenge_NUM_difficulty.fileExtension
Test case (INPUT): challenge_NUM_difficulty_TESTID.in
Test case (OUTPUT): challenge_NUM_difficulty_TESTID.out // where TESTID matches the TESTID of its input
```

"challenge" is included as a prefix to allow (for example) Java files to have a class name identical to the file name.

A handy regex for mass-renaming from `DD-MM_NUM_difficulty...` if necessary:
```sed
for item in *.* ;do git mv "$item" "$(echo "$item" | sed "s/[0-9]\+-[0-9]\+_\([0-9]\+_[a-zA-Z]\+.*\)/challenge_\1/" | awk '{print tolower($0)}')"; done
```

NOTE: Some of the in/outputs will be handled by `lbTest` where applicable (e.g. comparing a simple string input to a string output, etc. )

As of yet, I have no way of signifying that a thing is being handled by `lbTest`
