CC=g++
CPPFLAGS=-pedantic -Werror -Wall -Wextra
SRCS = overload2.cpp
OBJS = $(SRCS:.c=.o)
.PHONY: all
all: a.out
a.out: $(OBJS)
	$(CC) ${CPPFLAGS} -o $@ $^
$(OBJS):%.cpp
	$(CC) $(CPPFLAGS) -MM $< >$@ 
include $(SRCS:.c=.d)
.PHONY: g11
g11: CC += -std=c++11
.PHONY: gp
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
