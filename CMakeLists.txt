CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(dg-edit LANGUAGES CXX)

include_directories("include")

FIND_PACKAGE(FLTK REQUIRED)

ADD_LIBRARY(dg-edit-lib
    include/TextEditor.hpp src/TextEditor.cpp
)

ADD_EXECUTABLE(dg-edit src/main.cpp)
TARGET_LINK_LIBRARIES(dg-edit ${FLTK_LIBRARIES} dg-edit-lib)
