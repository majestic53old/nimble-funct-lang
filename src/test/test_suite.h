/*
 * test_suite.h
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

#ifndef TEST_SUITE_H_
#define TEST_SUITE_H_

#include <map>
#include "test.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef class _test_suite {
		
			public:

				_test_suite(void);

				_test_suite(
					__in const _test_suite &other
					);

				virtual ~_test_suite(void);

				_test_suite &operator=(
					__in const _test_suite &other
					);

				test &get_test(
					__in const std::string &name
					);

				size_t get_test_count(void);

				bool has_test(
					__in const std::string &name
					);

				bool is_result_valid(void);

				virtual void reset(void);

				void register_test(
					__in test &tst
					);

				void register_test(
					__in const std::string &name,
					__in test &tst
					);

				size_t run_all_tests(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				test_result run_test(
					__in const std::string &name,
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				virtual std::string to_string(
					__in bool verbose = false
					);

				void unregister_all_tests(void);

				void unregister_test(
					__in const std::string &name
					);

			protected:

				virtual void initialize(void);

				size_t m_run_count;

				std::map<std::string, test &> m_test_map;

			private:

				std::recursive_mutex m_test_suite_lock;

		} test_suite, *test_suite_ptr;
	}
}

#endif // TEST_SUITE_H_
