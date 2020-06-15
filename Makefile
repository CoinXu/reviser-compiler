CPP = g++
SOURCES_DIR = src
HEAD_FILE_PATH = $(shell pwd)/$(SOURCES_DIR)
COMPILE_CMD = $(CPP) -g -std=c++11 -I$(HEAD_FILE_PATH)

SRC = $(wildcard $(SOURCES_DIR)/*cpp) $(wildcard $(SOURCES_DIR)/**/*.cpp)

.SUFFIXES : .o .cpp .c
.cpp.o :
	$(COMPILE_CMD) $<
.c.o :
	$(COMPILE_CMD) $<

reviser: $(SRC)
	$(COMPILE_CMD) $^ -o build/$@

all: reviser

clean:
	rm build/*

.PHONY:
	clean
