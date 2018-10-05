/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <pthread.h>

extern void test_posix_clock(void);
extern void test_posix_mqueue(void);
extern void test_posix_normal_mutex(void);
extern void test_posix_recursive_mutex(void);
extern void test_posix_semaphore(void);
extern void test_posix_rw_lock(void);
extern void test_posix_realtime(void);
extern void test_posix_timer(void);

void test_main(void)
{
	ztest_test_suite(posix_apis,
			ztest_unit_test(test_posix_clock),
			ztest_unit_test(test_posix_semaphore),
			ztest_unit_test(test_posix_normal_mutex),
			ztest_unit_test(test_posix_recursive_mutex),
			ztest_unit_test(test_posix_mqueue),
			ztest_unit_test(test_posix_realtime),
			ztest_unit_test(test_posix_timer),
			ztest_unit_test(test_posix_rw_lock)
			);
	ztest_run_test_suite(posix_apis);
}
