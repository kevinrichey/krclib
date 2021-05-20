#include "test.h"

// Declare all test case functions.
// testcases.h is generated by discover_tests.awk.
#include "testcases.h"

typedef struct {
	TestCase test_case;
	const char *test_name;
} TestCaseRecord;

// NULL-terminated table of function pointers to all test cases.
// testcases.inc is generated by discover_tests.awk.
TestCaseRecord all_test_cases[] = {
#include "testcases.inc"
	{ NULL, "" }
};

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	printf("Testing\n");
	TestCounter test_counter = {0};

	int i;
	for (i = 0; all_test_cases[i].test_case; ++i) {
		test_counter.test_name = all_test_cases[i].test_name;
		all_test_cases[i].test_case(&test_counter);
	}

	if (test_counter.failure_count)
		printf("Failed!  ");
	else
		printf("Success! ");

	printf("[cases: %d, tests: %d, failures: %d]\n",
	       i, test_counter.test_count, test_counter.failure_count);

	return test_counter.failure_count;
}

void Test_assert(bool condition, TestCounter *counter, const char *file, int line, const char *msg)
{
	++counter->test_count;
	if (!condition) {
		printf("%s:%d: Test Failure: %s in test case %s()\n", file, line, msg, counter->test_name);
		++counter->failure_count;
	}
}

