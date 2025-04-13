TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = PakTool

INCLUDEPATH += $$PWD/lzo/include
DEPENDPATH += $$PWD/lzo/include

SOURCES += main.cpp \
    CFourCC.cpp \
    FileIO/CFileInStream.cpp \
    FileIO/CMemoryInStream.cpp \
    TropicalFreeze/CTropicalFreezePak.cpp \
    StringUtil.cpp \
    Compression.cpp \
    TropicalFreeze/DecompressLZSS.cpp \
    MREA.cpp \
    lzo/src/lzo1x_1.c \
    lzo/src/lzo1x_d1.c \
    lzo/src/lzo_util.c \
    lzo/src/lzo_init.c \
    lzo/src/lzo_ptr.c

HEADERS += \
    types.h \
    CFourCC.h \
    FileIO/FileIO.h \
    FileIO/CInputStream.h \
    FileIO/COutputStream.h \
    TropicalFreeze/SSectionHeader.h \
    TropicalFreeze/CTropicalFreezePak.h \
    TropicalFreeze/SRFRMHeader.h \
    TropicalFreeze/SFileID_128.h \
    StringUtil.h \
    PakList.h \
    Prime/CDependencyParser.h \
    Prime/CPrimePak.h \
    PakEnum.h \
    SAreaHeader.h \
    Corruption/CCorruptionPak.h \
    Compression.h \
    TropicalFreeze/DecompressLZSS.h \
    MREA.h
