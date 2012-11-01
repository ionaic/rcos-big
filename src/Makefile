# C Compiler
CC=g++
# Universal C Flags
CFLAGS+=-c -g
# Source Files
SOURCES=shellgen.cpp big.cpp
OBJECTS=$(SOURCES:.cpp=.o)
# Name of the output executable
NAME=../bin/big

all: $(SOURCES) $(NAME)

$(NAME): $(OBJECTS) 
	# $(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	# $(CC) $(CFLAGS) $(INCLUDEFLAGS) $< -o $@
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
