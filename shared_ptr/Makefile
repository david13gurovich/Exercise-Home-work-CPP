CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = shared_ptr.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all

.PHONY: all
all: a.out
a.out: test_shared_ptr.o
	$(CC) ${CPPFLAGS} $^ -o $@
test_shared_ptr.o: test_shared_ptr.cpp shared_ptr.hpp ../utils/test.hpp 
	$(CC) -c $(CPPFLAGS) -I ../utils/ test_shared_ptr.cpp -o $@

.PHONY: gc11
gc11: CC += -std=c++11 -Werror
gc11: all

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g
gd11: all

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
	rm -f *.o
