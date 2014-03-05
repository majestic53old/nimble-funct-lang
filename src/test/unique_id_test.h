/*
 * unique_id_test.h
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

#ifndef UNIQUE_ID_TEST_H_
#define UNIQUE_ID_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			UNIQUE_ID_TEST_DECREMENT_REFERENCE = 0,
			UNIQUE_ID_TEST_DESTROY,
			UNIQUE_ID_TEST_GENERATE,
			UNIQUE_ID_TEST_GET_REFERENCE_COUNT,
			UNIQUE_ID_TEST_INCREMENT_REFERENCE,
			UNIQUE_ID_TEST_INITIALIZE,
			UNIQUE_ID_TEST_IS_INITIALIZED,
			UNIQUE_ID_TEST_IS_REGISTERED,
			UNIQUE_ID_TEST_IS_UNIQUE,
			UNIQUE_ID_TEST_REGISTER_ID,
			UNIQUE_ID_TEST_REGISTRATION_COUNT,
		} unique_id_test_type;

		static const std::string UNIQUE_ID_TEST_STR[] = {
			"[Unique id] Decrement reference",
			"[Unique id] Destroy",
			"[Unique id] Generate",
			"[Unique id] Get reference count",
			"[Unique id] Increment reference",
			"[Unique id] Initialize",
			"[Unique id] Is initialized",
			"[Unique id] Is registered",
			"[Unique id] Is unique",
			"[Unique id] Register Id",
			"[Unique id] Registeration count",
			};

		#define MAX_UNIQUE_ID_TEST UNIQUE_ID_TEST_REGISTRATION_COUNT
		#define UNIQUE_ID_TEST_STRING(_TYPE_)\
			(((unique_id_test_type) _TYPE_) > (unique_id_test_type) MAX_UNIQUE_ID_TEST ? UNKNOWN : UNIQUE_ID_TEST_STR[_TYPE_])

		void unique_id_register_tests(
			__inout test_suite &suite
			);

		typedef class _unique_id_test_decrement_reference :
				public test {
		
			public:

				_unique_id_test_decrement_reference(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_DECREMENT_REFERENCE)) {}

				virtual ~_unique_id_test_decrement_reference(void) {}

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

		} unique_id_test_decrement_reference;

		typedef class _unique_id_test_destroy :
				public test {
		
			public:

				_unique_id_test_destroy(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_DESTROY)) {}

				virtual ~_unique_id_test_destroy(void) {}

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

		} unique_id_test_destroy;

		typedef class _unique_id_test_generate :
				public test {
		
			public:

				_unique_id_test_generate(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_GENERATE)) {}

				virtual ~_unique_id_test_generate(void) {}

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

		} unique_id_test_generate;

		typedef class _unique_id_test_get_reference_count :
				public test {
		
			public:

				_unique_id_test_get_reference_count(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_GET_REFERENCE_COUNT)) {}

				virtual ~_unique_id_test_get_reference_count(void) {}

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

		} unique_id_test_get_reference_count;

		typedef class _unique_id_test_increment_reference :
				public test {
		
			public:

				_unique_id_test_increment_reference(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_INCREMENT_REFERENCE)) {}

				virtual ~_unique_id_test_increment_reference(void) {}

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

		} unique_id_test_increment_reference;

		typedef class _unique_id_test_initialize :
				public test {
		
			public:

				_unique_id_test_initialize(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_INITIALIZE)) {}

				virtual ~_unique_id_test_initialize(void) {}

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

		} unique_id_test_initialize;

		typedef class _unique_id_test_is_initialized :
				public test {
		
			public:

				_unique_id_test_is_initialized(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_IS_INITIALIZED)) {}

				virtual ~_unique_id_test_is_initialized(void) {}

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

		} unique_id_test_is_initialized;

		typedef class _unique_id_test_is_registered :
				public test {
		
			public:

				_unique_id_test_is_registered(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_IS_REGISTERED)) {}

				virtual ~_unique_id_test_is_registered(void) {}

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

		} unique_id_test_is_registered;

		typedef class _unique_id_test_is_unique :
				public test {
		
			public:

				_unique_id_test_is_unique(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_IS_UNIQUE)) {}

				virtual ~_unique_id_test_is_unique(void) {}

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

		} _unique_id_test_is_unique;

		typedef class _unique_id_test_register_id :
				public test {
		
			public:

				_unique_id_test_register_id(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_REGISTER_ID)) {}

				virtual ~_unique_id_test_register_id(void) {}

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

		} unique_id_test_register_id;

		typedef class _unique_id_test_registration_count :
				public test {
		
			public:

				_unique_id_test_registration_count(void) :
					test(UNIQUE_ID_TEST_STRING(UNIQUE_ID_TEST_REGISTRATION_COUNT)) {}

				virtual ~_unique_id_test_registration_count(void) {}

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

		} unique_id_test_registration_count;
	}
}

#endif // UNIQUE_ID_TEST_H_
