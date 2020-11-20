/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>

struct StringBuilder;

extern struct StringBuilder* make_sb(void);
extern struct StringBuilder* make_sb_sized(size_t length);
extern int sb_append_len(struct StringBuilder* this, const char* s, size_t length);
extern int sb_append(struct StringBuilder* this, const char* s);
extern const char* sb_string(struct StringBuilder* this);
