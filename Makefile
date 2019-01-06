CXXFLAGS=-O3 -fvisibility=hidden
TARGET=libdsputils.so
VERSION=0

all: ${TARGET}

clean:
	rm -f ${TARGET} libdsputils.o

${TARGET}: libdsputils.o
	${CXX} -shared -Wl,-soname,${TARGET}.${VERSION} -o ${TARGET} $<

libdsputils.o: libdsputils.cpp
