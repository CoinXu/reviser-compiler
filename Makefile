CPP = g++
HEAD_FILE_PATH = ./
COMPILE_CMD = $(CPP) -I $(HEAD_FILE_PATH)

.SUFFIXES : .o .cpp .c
.cpp.o :
	$(COMPILE_CMD) $<
.c.o :
	$(COMPILE_CMD) $<

reviser-parser: ./main.cpp
	${COMPILE_CMD} -o $@ ./main.cpp

clean:
	rm reviser-parser

.PHONY:
	clean