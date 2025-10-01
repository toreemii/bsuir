# CMake generated Testfile for 
# Source directory: /home/vika/Рабочий стол/ppois
# Build directory: /home/vika/Рабочий стол/ppois/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTests "/home/vika/Рабочий стол/ppois/build/tests")
set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "/home/vika/Рабочий стол/ppois/CMakeLists.txt;36;add_test;/home/vika/Рабочий стол/ppois/CMakeLists.txt;0;")
subdirs("googletest")
