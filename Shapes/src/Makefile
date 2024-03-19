CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = shape.cpp test_shape.cpp line.cpp circle.cpp square.cpp rectangle.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all:a.out
a.out: shape.o test_shape.o line.o circle.o square.o rectangle.o group.o
	$(CC) ${CPPFLAGS} $^ -o $@  -Wl,-rpath=. ../lib/libglut_utils.so ../lib/libpoint.a
shape.o: shape.cpp ../include/shape.hpp
	$(CC) -c $(CPPFLAGS) shape.cpp -I ../include -o $@ 
test_shape.o: shape.cpp test_shape.cpp ../include/shape.hpp line.cpp circle.cpp shape.cpp rectangle.cpp group.cpp
	$(CC) -c $(CPPFLAGS) -I ../include test_shape.cpp -o $@
line.o: shape.cpp line.cpp ../include/line.hpp
	$(CC) -c $(CPPFLAGS) line.cpp -I ../include -o $@ 
circle.o: shape.cpp circle.cpp ../include/circle.hpp
	$(CC) -c $(CPPFLAGS) circle.cpp -I ../include -o $@ 
square.o: shape.cpp rectangle.cpp square.cpp ../include/square.hpp
	$(CC) -c $(CPPFLAGS) square.cpp -I ../include -o $@ 
rectangle.o: shape.cpp rectangle.cpp ../include/rectangle.hpp
	$(CC) -c $(CPPFLAGS) rectangle.cpp -I ../include -o $@ 
group.o: shape.cpp group.cpp ../include/group.hpp
	$(CC) -c $(CPPFLAGS) group.cpp -I ../include -o $@ 

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all

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
