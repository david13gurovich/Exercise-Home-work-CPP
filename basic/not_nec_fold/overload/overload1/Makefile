CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = fanc_overlapping.cpp
DEPFLAGS ?= -MMD -MP
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

-include $(DEPS)

.PHONY: all
all: a.out
a.out: fanc_overlapping.o
	$(CC) ${CPPFLAGS} fanc_overlapping.o -o $@
fanc_overlapping.o: fanc_overlapping.cpp
	$(CC) -c $(CPPFLAGS) $(DEPFLAGS) fanc_overlapping.cpp -o $@

foo.o: foo.cpp
	$(CC) -c $(CPPFLAGS) $(DEPFLAGS) foo.cpp -o $@

.PHONY: gc11
gc11: CC += -std=c++11 -Werror

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g

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
