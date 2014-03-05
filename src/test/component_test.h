/*
 * component_test.h
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

#ifndef COMPONENT_TEST_H_
#define COMPONENT_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			COMPONENT_TEST_DESTROY = 0,
			COMPONENT_TEST_INITIALIZE,
		} component_test_type;

		static const std::string COMPONENT_TEST_STR[] = {
			"[Component] Destroy",
			"[Component] Initialize",
			};

		#define MAX_COMPONENT_TEST COMPONENT_TEST_INITIALIZE
		#define COMPONENT_TEST_STRING(_TYPE_)\
			(((component_test_type) _TYPE_) > (component_test_type) MAX_COMPONENT_TEST ? UNKNOWN : COMPONENT_TEST_STR[_TYPE_])

		void component_register_tests(
			__inout test_suite &suite
			);

		typedef class _component_test_destroy :
				public test {
		
			public:

				_component_test_destroy(void) :
					test(COMPONENT_TEST_STRING(COMPONENT_TEST_DESTROY)) {}

				virtual ~_component_test_destroy(void) {}

			protected:

				virtual test_result run_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				virtual void setup_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				virtual void teardown_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

		} component_test_destroy;

		typedef class _component_test_initialize :
				public test {
		
			public:

				_component_test_initialize(void) :
					test(COMPONENT_TEST_STRING(COMPONENT_TEST_INITIALIZE)) {}

				virtual ~_component_test_initialize(void) {}

			protected:

				virtual test_result run_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				virtual void setup_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

				virtual void teardown_test(
					__in uintptr_t context = NULL,
					__in size_t length = 0
					);

		} component_test_initialize;
	}
}

#endif // COMPONENT_TEST_H_
