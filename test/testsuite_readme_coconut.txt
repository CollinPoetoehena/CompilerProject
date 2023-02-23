
1) Download the testsuite
2) Copy all files/folders except the run.bash to the test(this needs to be called test as provided by the skeleton) directory in your repository
3) Copy the run.bash file from Canvas/CoCoNut framework and place this inside your test directory.

You can now use ctest from without your build directory.
For example:
build-debug/$ ctest 
^^^^^^^^^^^   ^^^^^^^ 
(working dir  Shell command)
runs all tests.

Only want to run a specific test? Use the -R flag
build-debug/$ ctest -R basic

Want more output? Use --verbose 
build-debug/$ ctest --verbose

etc. Read the man page for more info.
