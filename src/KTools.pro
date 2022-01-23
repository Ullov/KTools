CONFIG += qt

TEMPLATE = lib
DEFINES += KTOOLS_LIBRARY

CONFIG += c++17 object_parallel_to_source

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp_h/HtmlAstMaker/object.cpp \
    cpp_h/HtmlAstMaker/tag.cpp \
    cpp_h/Kff/file.cpp \
    cpp_h/Kff/fixedtypes.cpp \
    cpp_h/Kff/list.cpp \
    cpp_h/Kff/manager.cpp \
    cpp_h/Kff/metainfofs.cpp \
    cpp_h/Kff/pointer.cpp \
    cpp_h/Kff/rawstream.cpp \
    cpp_h/Kff/string.cpp \
    cpp_h/Kff/variabletypes.cpp \
    cpp_h/StaticVarsDeclarations.cpp \
    cpp_h/archiverw.cpp \
    cpp_h/converter.cpp \
    cpp_h/curl.cpp \
    cpp_h/exforstring.cpp \
    cpp_h/file.cpp \
    cpp_h/fileidentifier.cpp \
    cpp_h/log.cpp \
    cpp_h/options.cpp \
    cpp_h/uuidslist.cpp \
    ktools.cpp

HEADERS += \
    KTools_global.h \
    cpp_h/HtmlAstMaker/object.h \
    cpp_h/HtmlAstMaker/tag.h \
    cpp_h/Kff/file.h \
    cpp_h/Kff/fixedtypes.h \
    cpp_h/Kff/list.h \
    cpp_h/Kff/manager.h \
    cpp_h/Kff/metainfofs.h \
    cpp_h/Kff/nameinfo.h \
    cpp_h/Kff/pointer.h \
    cpp_h/Kff/rawstream.h \
    cpp_h/Kff/string.h \
    cpp_h/Kff/variabletypes.h \
    cpp_h/archiverw.h \
    cpp_h/converter.h \
    cpp_h/curl.h \
    cpp_h/enums.h \
    cpp_h/exforstring.h \
    cpp_h/file.h \
    cpp_h/fileidentifier.h \
    cpp_h/log.h \
    cpp_h/options.h \
    cpp_h/uuidslist.h \
    ktools.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -lKF5Archive

RESOURCES += \
    resource.qrc
