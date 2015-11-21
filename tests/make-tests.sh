#!/usr/bin/env bash

# Auto generate single AllTests file for CuTest.
# Searches through all *.cpp files in the current directory.
# Prints to stdout.
# Author: Asim Jalis
# Date: 01/08/2003

# Modified by Guillaume Huysmans to return the count
# of failed tests as exit code.

if test $# -eq 0 ; then FILES=*.cpp ; else FILES=$* ; fi

echo '

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"

'

cat $FILES | grep '^void Test' |
    sed -e 's/(.*$//' \
        -e 's/$/(CuTest*);/' \
        -e 's/^/extern /'

echo \
'

int RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    int ret;

'
cat $FILES | grep '^void Test' |
    sed -e 's/^void //' \
        -e 's/(.*$//' \
        -e 's/^/    SUITE_ADD_TEST(suite, /' \
        -e 's/$/);/'

echo \
'
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    ret = suite->failCount;
    CuSuiteDelete(suite);
    return ret;
}

int main(void)
{
    return RunAllTests();
}
'
