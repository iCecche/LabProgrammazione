cmake_minimum_required(VERSION 3.30)
project(Notes)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)
add_executable(Notes src/main.cpp
        src/Note.cpp
        src/Note.h
        src/NoteCollection.cpp
        src/NoteCollection.h
        src/CollectionGroup.cpp
        src/CollectionGroup.h
        src/Observer.h
        src/Observable.h
        )
