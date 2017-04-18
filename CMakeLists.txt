cmake_minimum_required(VERSION 3.6)
project(GetSnippet)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp SnippetMaker/SnippetMaker.cpp SnippetMaker/DataPreparator.h SnippetMaker/DataPreparator.cpp Util/Includes.h Util/Utils.h Util/Utils.cpp)
add_executable(GetSnippet ${SOURCE_FILES})