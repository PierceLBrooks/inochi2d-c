cmake_minimum_required(VERSION 3.10)

include(FetchContent)

project(Inochi2D)

set(SFML_VERSION "2.5.1")

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)

if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

add_library(libinochi2d SHARED IMPORTED)
set_target_properties(libinochi2d PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/out/${CMAKE_SHARED_LIBRARY_PREFIX}inochi2d-c${CMAKE_SHARED_LIBRARY_SUFFIX})

include_directories(${sfml_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

add_definitions(-DINOCHI2D_GLYES)

add_executable(inochi2d
    ${SRCS}
)

target_link_libraries(inochi2d
    PRIVATE
        libinochi2d
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
)

target_compile_features(inochi2d PRIVATE cxx_std_14)

install(TARGETS inochi2d)

