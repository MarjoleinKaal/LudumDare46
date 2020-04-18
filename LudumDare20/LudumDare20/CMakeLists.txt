# CMakeList.txt : CMake project for LudumDare20, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file( GLOB_RECURSE GLOB_SOURCES *.c *.cpp *.h)
file( GLOB_RECURSE GLOB_HEADERS *.h)

# Add source to this project's executable.
add_executable (LudumDare20 ${GLOB_SOURCES})

# TODO: Add tests and install targets if needed.
target_link_libraries(LudumDare20 raylib)
target_link_libraries(LudumDare20 reactphysics3d)