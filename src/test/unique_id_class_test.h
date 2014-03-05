/*
 * unique_id_class_test.h
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

#ifndef UNIQUE_ID_CLASS_TEST_H_
#define UNIQUE_ID_CLASS_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			UNIQUE_ID_CLASS_TEST_ASSIGNMENT = 0,
			UNIQUE_ID_CLASS_TEST_DESTRUCTION,
			UNIQUE_ID_CLASS_TEST_GET_ID,
			UNIQUE_ID_CLASS_TEST_GET_REFERENCE_COUNT,
			UNIQUE_ID_CLASS_TEST_INSTANTIATION,
			UNIQUE_ID_CLASS_TEST_IS_UNIQUE,
			UNIQUE_ID_CLASS_TEST_SET_ID,
		} unique_id_class_test_type;

		static const std::string UNIQUE_ID_CLASS_TEST_STR[] = {
			"[Unique id class] Class assignment",
			"[Unique id class] Class destruction",
			"[Unique id class] Get id",
			"[Unique id class] Get reference count",
			"[Unique id class] Class instantiation",
			"[Unique id class] Is unique",
			"[Unique id class] Set id",
			};

		#define MAX_UNIQUE_ID_CLASS_TEST UNIQUE_ID_CLASS_TEST_SET_ID
		#define UNIQUE_ID_CLASS_TEST_STRING(_TYPE_)\
			(((unique_id_class_test_type) _TYPE_) > (unique_id_class_test_type) MAX_UNIQUE_ID_CLASS_TEST ? UNKNOWN : UNIQUE_ID_CLASS_TEST_STR[_TYPE_])

		void unique_id_class_register_tests(
			__inout test_suite &suite
			);

		typedef class _unique_id_class_test_assignment :
				public test {
		
			public:

				_unique_id_class_test_assignment(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_ASSIGNMENT)) {}

				virtual ~_unique_id_class_test_assignment(void) {}

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

		} unique_id_class_test_assignment;

		typedef class _unique_id_class_test_destruction :
				public test {
		
			public:

				_unique_id_class_test_destruction(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_DESTRUCTION)) {}

				virtual ~_unique_id_class_test_destruction(void) {}

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

		} unique_id_class_test_destruction;

		typedef class _unique_id_class_test_get_id :
				public test {
		
			public:

				_unique_id_class_test_get_id(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_GET_ID)) {}

				virtual ~_unique_id_class_test_get_id(void) {}

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

		} unique_id_class_test_get_id;

		typedef class _unique_id_class_test_get_reference_count :
				public test {
		
			public:

				_unique_id_class_test_get_reference_count(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_GET_REFERENCE_COUNT)) {}

				virtual ~_unique_id_class_test_get_reference_count(void) {}

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

		} unique_id_class_test_get_reference_count;

		typedef class _unique_id_class_test_instantiation :
				public test {
		
			public:

				_unique_id_class_test_instantiation(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_INSTANTIATION)) {}

				virtual ~_unique_id_class_test_instantiation(void) {}

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

		} unique_id_class_test_instantiation;

		typedef class _unique_id_class_test_is_unique :
				public test {
		
			public:

				_unique_id_class_test_is_unique(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_IS_UNIQUE)) {}

				virtual ~_unique_id_class_test_is_unique(void) {}

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

		} unique_id_class_test_is_unique;

		typedef class _unique_id_class_test_set_id :
				public test {
		
			public:

				_unique_id_class_test_set_id(void) :
					test(UNIQUE_ID_CLASS_TEST_STRING(UNIQUE_ID_CLASS_TEST_SET_ID)) {}

				virtual ~_unique_id_class_test_set_id(void) {}

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

		} unique_id_class_test_set_id;
	}
}

#endif // UNIQUE_ID_CLASS_TEST_H_
