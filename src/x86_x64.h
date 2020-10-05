/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdint.h>

#if UINTPTR_MAX > 0xffffffffU
#define PF_SIZE_T "%lu"
#else
#define PF_SIZE_T "%u"
#endif
