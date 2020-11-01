/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
 * see https://stackoverflow.com/questions/430424/are-there-any-macros-to-determine-if-my-code-is-being-compiled-to-windows
 */
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || \
    defined(_MSC_VER) || defined(__BORLANDC__)
#define OS_WINDOWS
#define OS_SLASH "\\"
#else
#define OS_LINUX
#define OS_SLASH "/"
#endif
