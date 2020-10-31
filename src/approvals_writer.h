/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
extern const char* approvals_get_received_file_name(const char* full_file_name,
                                                    const char* test_name,
                                                    const char* extension_no_dot);
extern const char* approvals_get_approved_file_name(const char* full_file_name,
                                                    const char* test_name,
                                                    const char* extension_no_dot);

// interface ApprovalWriter {
//     String writeReceivedFile(String var1);
//     String getReceivedFilename(String var1);
//     String getApprovalFilename(String var1);
// }
