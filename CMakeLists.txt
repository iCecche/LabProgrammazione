cmake_minimum_required(VERSION 3.30)
project(Notes)

set(CMAKE_CXX_STANDARD 20)

add_executable(Notes main.cpp
        Note.cpp
        Note.h
        NoteCollection.cpp
        NoteCollection.h)
