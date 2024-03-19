CC=g++
CPPFLAGS=-pedantic -Werror -Wall -Wextra
SRCS = point.cpp test_point.cpp
DEPFLAGS ?= -MMD -MP
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

-include $(DEPS)
.PHONY: all
all: a.out
a.out: point.o test_point.o
	$(CC) ${CPPFLAGS} point.o test_point.o -o $@
point.o: point.cpp

test_point.o: test_point.cpp

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
