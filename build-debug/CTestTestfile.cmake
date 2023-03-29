# CMake generated Testfile for 
# Source directory: /home/poetoec/CompilerConstruction/CompilerProject/CompilerProject
# Build directory: /home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(basic "/run.bash" "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/civicc" "basic")
set_tests_properties(basic PROPERTIES  WORKING_DIRECTORY "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/test" _BACKTRACE_TRIPLES "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;12;add_test;/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;0;")
add_test(nested_funs "/run.bash" "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/civicc" "nested_funs")
set_tests_properties(nested_funs PROPERTIES  WORKING_DIRECTORY "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/test" _BACKTRACE_TRIPLES "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;13;add_test;/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;0;")
add_test(arrays "/run.bash" "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/civicc" "arrays")
set_tests_properties(arrays PROPERTIES  WORKING_DIRECTORY "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/test" _BACKTRACE_TRIPLES "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;14;add_test;/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/CMakeLists.txt;0;")
subdirs("palm")
