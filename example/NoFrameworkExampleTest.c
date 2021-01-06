/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <approvals.h> /* see https://github.com/codecop/ApprovalTests.c */

static void test_one(void)
{
    verify_txt("text");
}

int main(void)
{
    test_one();
    return 0;
}
