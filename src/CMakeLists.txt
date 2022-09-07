cmake_minimum_required(VERSION 3.20)
project(KTools VERSION 0.1.1 LANGUAGES CXX C)

add_compile_definitions(KT_DEBUG)
set(CMAKE_CXX_STANDART 23)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(MAKE_SHARED ON)
#set(MAKE_STATIC ON)

add_compile_options(-std=c++23)

set(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/connection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/requesthandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/socket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/cookies.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/header.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/reqresdata.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/response.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/request.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/bio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/ssl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Html/ast.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Html/tag.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/StaticVarsDeclarations.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/archiverw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/converter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/curl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/exforstring.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/file.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/fileidentifier.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/log.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/options.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/uuidslist.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ktools.cpp

    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/connection.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/requesthandler.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/socket.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/cookies.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/header.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/reqresdata.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/response.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/request.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/client.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/bio.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/ssl.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Network/Ssl/client.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Html/ast.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/Html/tag.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/archiverw.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/converter.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/curl.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/enums.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/exforstring.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/file.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/fileidentifier.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/log.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/options.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_h/uuidslist.h
    ${CMAKE_CURRENT_LIST_DIR}/ktools.h
    ${CMAKE_CURRENT_LIST_DIR}/KTools_global.h

# C files
    ${CMAKE_CURRENT_LIST_DIR}/c/utils.c

    ${CMAKE_CURRENT_LIST_DIR}/c/utils.h
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
