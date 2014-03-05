/*
 * test_type.h
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

#ifndef TEST_TYPE_H_
#define TEST_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			TEST_EXCEPTION_INVALID_NAME = 0,
		} test_exception_type;

		static const std::string TEST_EXCEPTION_STR[] = {
			"Invalid test name",
			};

		static const std::string TEST_RESULT_STR[] = {
			"SUCCESS", "FAILURE", "INCONCLUSIVE",
			};

		#define MAX_TEST_EXCEPTION TEST_EXCEPTION_INVALID_NAME
		#define MAX_TEST_RESULT TEST_RESULT_INCONCLUSIVE
		#define TEST_HEADER "TEST"
		#define TEST_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_TEST_EXCEPTION ? UNKNOWN_EXCEPTION : TEST_EXCEPTION_STR[_TYPE_])
		#define TEST_RESULT_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_TEST_RESULT ? UNKNOWN : TEST_RESULT_STR[_TYPE_])
		#define THROW_TEST_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(TEST_HEADER, TEST_RESULT_STRING(_TYPE_))
		#define THROW_TEST_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(TEST_HEADER, TEST_RESULT_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _test;
		typedef _test test, *test_ptr;
	}
}

#endif // TEST_TYPE_H_
