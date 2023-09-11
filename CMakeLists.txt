cmake_minimum_required(VERSION 3.10)

project(pingpong)

set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCE CONFIGURE_DEPENDS "*.h" "*.cpp")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/settings.txt
     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Debug)

add_executable(pingpong WIN32 ${SOURCE})

target_link_libraries(pingpong PRIVATE winmm.lib gdi32.lib)

