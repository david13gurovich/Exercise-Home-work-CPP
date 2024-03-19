CC=g++
CPPFLAGS=-pedantic -Werror -Wall -Wextra
SRCS = ctor_dtor.cpp
DEPFLAGS ?= -MMD -MP
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

-include $(DEPS)
.PHONY: all
all: a.out
a.out: ctor_dtor.o
	$(CC) ${CPPFLAGS} ctor_dtor.o -o $@

ctor_dtor.o: ctor_dtor.cpp

.PHONY: g11
g11: CC += -std=c++11

.PHONY: gp
gp: CPPFLAGS += -g
gp: all

.PHONY: gpr
gpr: CPPFLAGS +=  -DNDEBUG -O3
gpr: all

.PHONY: debug
debug:
	echo $(TARGET_LIB)

.PHONY: clean
clean:
	rm -f *.o *.d
