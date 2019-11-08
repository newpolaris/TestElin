cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED native-lib.cpp renderer.cpp)

include_directories(include)

find_library(log-lib log android EGL GLES2)

target_link_libraries(native-lib ${log-lib} EGL GLESv2 android)
