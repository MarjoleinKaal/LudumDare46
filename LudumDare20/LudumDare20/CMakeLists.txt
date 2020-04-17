# CMakeList.txt : CMake project for LudumDare20, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (LudumDare20 "Main.cpp" "Main.h")

# TODO: Add tests and install targets if needed.
target_link_libraries(LudumDare20 raylib)
target_link_libraries(LudumDare20 reactphysics3d)