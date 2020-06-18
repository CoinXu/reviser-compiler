CPP = g++
SOURCES_DIR = src
HEAD_FILE_PATH = $(shell pwd)/$(SOURCES_DIR)
COMPILE_CMD = $(CPP) -g -std=c++11 -I$(HEAD_FILE_PATH)
LIB_NAME = reviserc

SRC = $(wildcard $(SOURCES_DIR)/*cpp) $(wildcard $(SOURCES_DIR)/**/*.cpp)

.SUFFIXES : .o .cpp .c
.cpp.o :
	$(COMPILE_CMD) $<
.c.o :
	$(COMPILE_CMD) $<

$(LIB_NAME): $(SRC)
	$(COMPILE_CMD) $^ -o build/$@

install:
	make $(LIB_NAME)
	cp build/$(LIB_NAME) /usr/bin

uninstall:
	rm /usr/bin/$(LIB_NAME)

all: $(LIB_NAME)

clean:
	rm build/*

.PHONY:
	clean
