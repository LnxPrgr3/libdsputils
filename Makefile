CXXFLAGS=-O3 -fvisibility=hidden
TARGET=libdsputils.so
VERSION=0

all: ${TARGET}

clean:
	rm -f ${TARGET} statistics.o

${TARGET}: statistics.o
	${CXX} ${CXXFLAGS} -shared -Wl,-soname,${TARGET}.${VERSION} -o ${TARGET} $<

statistics.o: statistics.cpp
