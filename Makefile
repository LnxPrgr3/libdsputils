CXXFLAGS=-O3 -fvisibility=hidden -fPIC
TARGET=libdsputils.so
VERSION=0

all: ${TARGET}

clean:
	rm -f ${TARGET} statistics.o constants.o noise.o

${TARGET}: statistics.o constants.o noise.o
	${CXX} ${CXXFLAGS} -shared -Wl,-soname,${TARGET}.${VERSION} -o ${TARGET} $^

statistics.o: statistics.cpp include/statistics.h
noise.o: noise.cpp include/noise.h
constants.o: constants.cpp include/constants.h
