cmake_minimum_required(VERSION 3.0.0)
project(raytracer CXX)

# include(CTest)
# enable_testing()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native")

set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "Build a static (.a) version of the library")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(assimp)
include_directories("${PROJECT_SOURCE_DIR}/assimp/include")

include_directories(includes/ assimp/include/)
file(GLOB SRC src/*.cc)
# include_directories(
#     ${PROJECT_SOURCE_DIR}/includes/
#     ${PROJECT_SOURCE_DIR}/src/
# )
add_executable(raytracer ${SRC})
target_link_libraries(raytracer assimp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
