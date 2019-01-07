CXXFLAGS=-O3 -fvisibility=hidden -fPIC
TARGET=libdsputils.so
VERSION=0

all: ${TARGET}

clean:
	rm -f ${TARGET} statistics.o constants.o

${TARGET}: statistics.o constants.o
	${CXX} ${CXXFLAGS} -shared -Wl,-soname,${TARGET}.${VERSION} -o ${TARGET} $<

statistics.o: statistics.cpp include/statistics.h
constants.o: constants.cpp include/constants.h
