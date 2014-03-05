/*
 * test.h
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

#ifndef TEST_H_
#define TEST_H_

#include "type.h"

namespace NIMBLE_NS {

	#ifndef TEST_NS
	#define TEST_NS test
	#endif // TEST_NS

	namespace TEST_NS {

		typedef enum {
			TEST_RESULT_SUCCESS = 0,
			TEST_RESULT_FAILURE,
			TEST_RESULT_INCONCLUSIVE,
		} test_result;

		typedef class _test {
	
			public:

				_test(
					__in const std::string &name
					);

				_test(
					__in const _test &other
					);

				virtual ~_test(void);

				_test &operator=(
					__in const _test &other
					);

				std::string get_name(void);

				test_result get_result(void);

				bool is_result_valid(void);

				virtual void reset(void);

				test_result run(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				void set_name(
					__in const std::string &name
					);

				virtual std::string to_string(
					__in bool verbose = false
					);

			protected:

				virtual test_result run_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					) = 0;

				virtual void setup_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					) = 0;

				virtual void teardown_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					) = 0;

				std::string m_name;

				test_result m_result;

				size_t m_run_count;

			private:

				std::recursive_mutex m_test_lock;

		} test, *test_ptr;
	}
}

#endif // TEST_H_
