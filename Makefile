TARGET = parser

CXX      = g++
CXXFLAGS = -std=c++20

SRCS = $(wildcard src/*.cpp)
BUILD_DIR = build

.PHONY: all build_dir compdb clean

all: build_dir ${SRCS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${BUILD_DIR}/${TARGET}

build_dir:
	mkdir -p build

compdb: build_dir
	bear -- make all

clean:
	rm -rf ${BUILD_DIR}
