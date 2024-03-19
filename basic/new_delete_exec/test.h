#ifndef TEST_H_
#define TEST_H_

#include <stdio.h> /* fprintf */

typedef enum {TEST_FAIL = 0, TEST_PASS =1} TestResult;

#define REQUIRE(cond) \
do{\
	if (!(cond)) {\
		fprintf(stderr, "\nTest failed at %s : %d  for: %s", \
			__FILE__, __LINE__,#cond); \
		return TEST_FAIL;\
	}\
}while(0)


#define REQUIRE_WITH_INDEX(cond,i) \
do{\
	if (!(cond)) {\
		fprintf(stderr, "\nTest failed at %s : %d  for: %s, test#: %lu", \
			__FILE__, __LINE__,#cond, i); \
		return TEST_FAIL;\
	}\
}while(0) 



#define RUN_TEST(test) \
do { \
	fprintf(stderr, "Running "#test"... "); \
	if (test() == TEST_PASS) { \
		fprintf(stderr, "\t[Ok]\n"); \
	} else { \
		fprintf(stderr, "\t[Failed]\n"); \
	} \
} while(0)


#endif /* TEST_H_ */
