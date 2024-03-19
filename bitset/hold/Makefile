CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = bitset.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: a.out
a.out: test_bitset.o 
	$(CC) ${CPPFLAGS} $^ -o $@
test_bitset.o: test_bitset.cpp bitset.hpp ../utils/test.hpp 
	$(CC) -c $(CPPFLAGS) -I ../utils/ test_bitset.cpp -o $@

.PHONY: gc11
gc11: CC += -std=c++11 -Werror
gc11: all

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g
gd11: all

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all

.PHONY: gdpp
gdpp: CPPFLAGS += -std=c++98 -Werror -g
gdpp: all

.PHONY: gcp
gcp: CPPFLAGS += -std=c++98 -Werror -DNDEBUG -O3
gcp: all

.PHONY: debug
debug:
	echo $(TARGET_LIB)

.PHONY: clean
clean:
	rm -f *.o *.d
