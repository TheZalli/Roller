TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/Absyn.cpp \
    src/Lexer.cpp \
    src/Printer.cpp \
    src/Skeleton.cpp \
    src/Parser.cpp

OTHER_FILES +=

HEADERS += \
    src/Absyn.H \
    src/Parser.H \
    src/Printer.H \
    src/Skeleton.H

