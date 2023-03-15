# CMake generated Testfile for 
# Source directory: /home/gene/Coding/IVSigma/snippets
# Build directory: /home/gene/Coding/IVSigma/build/snippets
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_snippet_char_to_rank.cpp "bash" "-c" "/home/gene/Coding/IVSigma/build/snippets/snippet_char_to_rank.cpp | diff - /home/gene/Coding/IVSigma/snippets/char_to_rank.cpp.out")
set_tests_properties(test_snippet_char_to_rank.cpp PROPERTIES  _BACKTRACE_TRIPLES "/home/gene/Coding/IVSigma/snippets/CMakeLists.txt;7;add_test;/home/gene/Coding/IVSigma/snippets/CMakeLists.txt;11;test_snippet;/home/gene/Coding/IVSigma/snippets/CMakeLists.txt;0;")
