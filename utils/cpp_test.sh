mkdir $1

echo '#include "'$1'.hpp"' >> $1/$1.cpp

echo -n '#ifndef ILRD_RD61_' >> $1/$1.hpp
echo -n $1 | tr [a-z] [A-Z] >> $1/$1.hpp
echo '_HPP' >> $1/$1.hpp
echo -n '#define ILRD_RD61_' >> $1/$1.hpp
echo -n $1 | tr [a-z] [A-Z] >> $1/$1.hpp
echo '_HPP' >> $1/$1.hpp
echo '#endif' >> $1/$1.hpp

echo '#include <cstdlib>

#include "test.hpp"
#include "'$1'.hpp"

TestResult TestAdd();

int main()
{
	RUN_TEST(TestAdd);


	return (EXIT_SUCCESS);
}

TestResult TestAdd()
{
	REQUIRE(true);	

	return (TEST_PASS);
}' >> $1/test_$1.cpp

echo 'CC=g++' >> $1/Makefile
echo 'CPPFLAGS=-pedantic -Wall -Wextra' >> $1/Makefile
echo 'SRCS = '$1'.cpp' >> $1/Makefile
echo 'OBJS = $(SRCS:.cpp=.o)' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: gdp' >> $1/Makefile
echo 'gdp: CPPFLAGS += -std=c++98 -g' >> $1/Makefile
echo 'gdp: all' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: all' >> $1/Makefile
echo 'all: a.out' >> $1/Makefile
echo 'a.out: '$1'.o test_'$1'.o' >> $1/Makefile
echo '	$(CC) ${CPPFLAGS} $^ -o $@' >> $1/Makefile
echo $1'.o: '$1'.cpp' $1'.hpp'>> $1/Makefile
echo '	$(CC) -c $(CPPFLAGS) '$1'.cpp -o $@' >> $1/Makefile
echo 'test_'$1'.o: test_'$1'.cpp' $1'.hpp ~/git/fs_cpp/utils/test.hpp' >> $1/Makefile
echo '	$(CC) -c $(CPPFLAGS) -I ~/git/fs_cpp/utils/ test_'$1'.cpp -o $@' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: gc11' >> $1/Makefile
echo 'gc11: CC += -std=c++11 -Werror' >> $1/Makefile
echo 'gc11: all' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: gd11' >> $1/Makefile
echo 'gd11: CC += -std=c++11 -Werror -g' >> $1/Makefile
echo 'gd11: all' >> $1/Makefile
echo '' >> $1/Makefile

echo '.PHONY: gdpp' >> $1/Makefile
echo 'gdpp: CPPFLAGS += -std=c++98 -Werror -g' >> $1/Makefile
echo 'gdpp: all' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: gcp' >> $1/Makefile
echo 'gcp: CPPFLAGS += -std=c++98 -Werror -DNDEBUG -O3' >> $1/Makefile
echo 'gcp: all' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: debug' >> $1/Makefile
echo 'debug:' >> $1/Makefile
echo '	echo $(TARGET_LIB)' >> $1/Makefile
echo '' >> $1/Makefile
echo '.PHONY: clean' >> $1/Makefile
echo 'clean:' >> $1/Makefile
echo '	rm -f *.o' >> $1/Makefile
