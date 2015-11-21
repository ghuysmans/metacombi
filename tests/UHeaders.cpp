#include <stdlib.h>
#include <string.h>
#include "CuTest.h"

void TestHeaders(CuTest *tc) {
	CuAssertStrEquals(tc, "hello", "hello");
	//CuFail(tc, name);
}
