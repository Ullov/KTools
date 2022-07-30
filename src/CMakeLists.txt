cmake_minimum_required(VERSION 3.16)
project(KTools VERSION 0.1.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(MAKE_SHARED ON)
#set(MAKE_STATIC ON)

set(FILES
    cpp_h/HtmlAstMaker/object.cpp
    cpp_h/HtmlAstMaker/tag.cpp
    cpp_h/Network/connection.cpp
    cpp_h/Network/requesthandler.cpp
    cpp_h/Network/socket.cpp
    cpp_h/StaticVarsDeclarations.cpp
    cpp_h/archiverw.cpp
    cpp_h/converter.cpp
    cpp_h/curl.cpp
    cpp_h/exforstring.cpp
    cpp_h/file.cpp
    cpp_h/fileidentifier.cpp
    cpp_h/log.cpp
    cpp_h/options.cpp
    cpp_h/uuidslist.cpp
    ktools.cpp

    KTools_global.h
    cpp_h/HtmlAstMaker/object.h
    cpp_h/HtmlAstMaker/tag.h
    cpp_h/Network/connection.h
    cpp_h/Network/requesthandler.h
    cpp_h/Network/socket.h
    cpp_h/archiverw.h
    cpp_h/converter.h
    cpp_h/curl.h
    cpp_h/enums.h
    cpp_h/exforstring.h
    cpp_h/file.h
    cpp_h/fileidentifier.h
    cpp_h/log.h
    cpp_h/options.h
    cpp_h/uuidslist.h
    ktools.h
)

find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

add_library(Curl SHARED IMPORTED)
set_target_properties(Curl PROPERTIES IMPORTED_LOCATION -lcurl)

if (MAKE_SHARED)
    add_library(KTools SHARED "${FILES}")
    set_target_properties(KTools PROPERTIES VERSION "${PROJECT_VERSION}")
    target_include_directories(KTools PUBLIC .)
    target_link_libraries(KTools PRIVATE Qt6::Core)
    target_link_libraries(KTools PRIVATE Curl)
endif()


if (MAKE_STATIC)
    add_library(KTools_static STATIC "${FILES}")
    set_target_properties(KTools_static PROPERTIES VERSION "${PROJECT_VERSION}")
    target_include_directories(KTools_static PUBLIC .)
    target_link_libraries(KTools_static PRIVATE Qt6::Core)
    target_link_libraries(KTools_static PRIVATE Curl)
endif()
