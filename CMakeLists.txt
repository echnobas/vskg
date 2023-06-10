cmake_minimum_required(VERSION 3.5)
project(vs_kg)
add_executable(keygen main.cpp product_key.cpp)
target_link_libraries(keygen PUBLIC "C:\\Program Files\\LLVM\\lib\\clang\\16\\lib\\windows\\clang_rt.builtins-x86_64.lib")