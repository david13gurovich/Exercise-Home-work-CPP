CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = polygon.cpp test_polygons.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: a.out
a.out: test_polygons.o polygon.o point.o
	$(CC) ${CPPFLAGS} $^ -o $@
test_polygons.o: test_polygons.cpp polygon.hpp ../../../ds/utils/test.h
	$(CC) -c $(CPPFLAGS) -I ../../../ds/utils -I ../point test_polygons.cpp -o $@
polygon.o: polygon.cpp polygon.hpp ../point/point.h
	$(CC) -c $(CPPFLAGS) -I ../point polygon.cpp -o $@
point.o: ../point/point.cpp ../point/point.h
	$(CC) -c $(CPPFLAGS) -I ../point ../point/point.cpp -o $@

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
