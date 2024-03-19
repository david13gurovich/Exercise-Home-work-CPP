CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = new_delete_exec.cpp test_new_delete_exec.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: a.out
a.out: new_delete_exec.o test_new_delete_exec.o
	$(CC) ${CPPFLAGS} $^ -o $@

new_delete_exec.o: new_delete_exec.cpp new_delete_exec.hpp

test_new_delete_exec.o: test_new_delete_exec.cpp new_delete_exec.hpp

.PHONY: gc11
gc11: CC += -std=c++11 -Werror
gc11: all

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g
gd11: all

.PHONY: gdp
gdp: CPPFLAGS += -g
gdp: all

.PHONY: gdpp
gdpp: CPPFLAGS += -Werror -g
gdpp: all

.PHONY: gcp
gcp: CPPFLAGS += -Werror -DNDEBUG -O3
gcp: all

.PHONY: debug
debug:
	echo $(TARGET_LIB)

.PHONY: clean
clean:
	rm -f *.o *.d
