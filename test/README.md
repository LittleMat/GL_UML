# How to use the test

## On windows

1. Use Visual Studio and create a new project/solution for Google Test
2. Delete the "pch.h" "pch.cpp" "test.cpp" that came by default
3. Copy all files under src and the "unitTest.cpp" to the directory of the solution
4. Under Visual Studio, use "Project">"Add existing element" and add all these files
5. Remove the main function in any file
6. Right click on the project, go to "Properties", find "C/C++">"Precompiled headers" and disable it.
7. Go to "Test" and run all tests.

## On linux

Under linux, run `make test/Makefile` and then run `test/unitTest`
