Some information from me to future me

Directory structure is as follows:
```
dailyprogrammer/year/
dailyprogrammer/year/tests/
dailyprogrammer/year/Makefile (file) -> Used to `make clean`
```

Within each folder, each file is like this:
```
Solution: year/mm-dd_NUM_difficulty.fileExtension
Test case (INPUT): mm-dd_NUM_difficulty_TESTID.in
Test case (OUTPUT): mm-dd_NUM_difficulty_TESTID.out // where TESTID matches the TESTID of its input
```

NOTE: Some of the in/outputs will be handled by `lbTest` where applicable (e.g. comparing a simple string input to a string output, etc. )

As of yet, I have no way of signifying that a thing is being handled by `lbTest`
