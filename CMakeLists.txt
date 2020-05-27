cmake_minimum_required(VERSION 3.13)
project(tlpi C)

set(CMAKE_C_STANDARD 99)

find_package(Threads)

set(lib_root "lib")
set(lib_includedir "lib")
set(lib_librarydir "lib")


include_directories("${PROJECT_SOURCE_DIR}lib")

add_executable(tlpi main.c)
add_executable(glibversion glibversion.c)
add_executable(copy fileio/copy.c)


add_executable(01simple_thread c29thread/01simple_thread.c)
target_link_libraries(01simple_thread ${CMAKE_THREAD_LIBS_INIT})

add_executable(05strerror c30threadsync/05strerror.c)
add_executable(06strerror_test c30threadsync/06strerror_test.c)


