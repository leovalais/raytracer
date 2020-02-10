cmake_minimum_required(VERSION 3.0.0)
project(raytracer CXX)

# include(CTest)
# enable_testing()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native")

include_directories(includes)
file(GLOB SRC src/*.cc)
# include_directories(
#     ${PROJECT_SOURCE_DIR}/includes/
#     ${PROJECT_SOURCE_DIR}/src/
# )
add_executable(raytracer ${SRC})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
