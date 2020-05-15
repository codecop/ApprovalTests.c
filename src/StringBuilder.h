/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
struct StringBuilder;

extern struct StringBuilder* make_sb(void);
extern int sb_append(struct StringBuilder* this, const char* s);
extern const char* sb_string(struct StringBuilder* this);
