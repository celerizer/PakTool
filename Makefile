CXX := g++
CXXFLAGS := -O2 -I./lzo/include -I. -Wall -Wextra
LDFLAGS := -static
LIBS := -lz
TARGET := PakTool

SRC := main.cpp \
    CFourCC.cpp \
    FileIO/CFileInStream.cpp \
    FileIO/CFileOutStream.cpp \
    FileIO/CMemoryInStream.cpp \
    FileIO/CMemoryOutStream.cpp \
    FileIO/CTextOutStream.cpp \
    FileIO/CVectorOutStream.cpp \
    TropicalFreeze/CTropicalFreezePak.cpp \
    StringUtil.cpp \
    Compression.cpp \
    TropicalFreeze/DecompressLZSS.cpp \
    MREA.cpp \
    lzo/src/lzo1x_1.c \
    lzo/src/lzo1x_d1.c \
    lzo/src/lzo_util.c \
    lzo/src/lzo_init.c \
    lzo/src/lzo_ptr.c \
    lzo/src/lzo1x_9x.c

OBJ := $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -x c -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
