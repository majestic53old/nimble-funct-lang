/*
 * test_suite_type.h
 * Copyright (C) 2014 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEST_SUITE_TYPE_H_
#define TEST_SUITE_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			TEST_SUITE_EXCEPTION_TEST_ALREADY_REGISTERED = 0,
			TEST_SUITE_EXCEPTION_TEST_NOT_REGISTERED,
			TEST_SUITE_EXCEPTION_UNKNOWN_TEST,
			TEST_SUITE_EXCEPTION_UNKNOWN_TEST_RESULT,
		} test_suite_exception_type;

		static const std::string TEST_SUITE_EXCEPTION_STR[] = {
			"Test is already registered",
			"Test is not registered",
			"Unknown test",
			"Unknown test result",
			};

		#define MAX_TEST_SUITE_EXCEPTION TEST_SUITE_EXCEPTION_UNKNOWN_TEST
		#define TEST_SUITE_HEADER "TEST_SUITE"
		#define TEST_SUITE_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_TEST_SUITE_EXCEPTION ? UNKNOWN_EXCEPTION : TEST_SUITE_EXCEPTION_STR[_TYPE_])
		#define THROW_TEST_SUITE_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(TEST_SUITE_HEADER, TEST_SUITE_EXCEPTION_STRING(_TYPE_))
		#define THROW_TEST_SUITE_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(TEST_SUITE_HEADER, TEST_SUITE_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _test_suite;
		typedef _test_suite test_suite, *test_suite_ptr;
	}
}

#endif // TEST_SUITE_TYPE_H_
