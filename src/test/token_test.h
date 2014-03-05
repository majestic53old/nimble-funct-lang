/*
 * token_test.h
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

#ifndef TOKEN_TEST_H_
#define TOKEN_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			TOKEN_TEST_DECREMENT_REFERENCE = 0,
			TOKEN_TEST_DESTROY,
			TOKEN_TEST_GET_REFERENCE_COUNT,
			TOKEN_TEST_GET_TOKEN,
			TOKEN_TEST_INCREMENT_REFERENCE,
			TOKEN_TEST_INITIALIZE,
			TOKEN_TEST_IS_REGISTERED,
			TOKEN_TEST_REGISTER_TOKEN,
			TOKEN_TEST_REGISTRATION_COUNT,
		} token_test_type;

		static const std::string TOKEN_TEST_STR[] = {
			"[Token] Decrement reference",
			"[Token] Destroy",
			"[Token] Get reference count",
			"[Token] Get token",
			"[Token] Increment reference",
			"[Token] Initialize",
			"[Token] Is registered",
			"[Token] Register token",
			"[Token] Registration count",
			};

		#define MAX_TOKEN_TEST TOKEN_TEST_REGISTRATION_COUNT
		#define TOKEN_TEST_STRING(_TYPE_)\
			(((token_test_type) _TYPE_) > (token_test_type) MAX_TOKEN_TEST ? UNKNOWN : TOKEN_TEST_STR[_TYPE_])

		void token_register_tests(
			__inout test_suite &suite
			);

		typedef class _token_test_decrement_reference :
				public test {
		
			public:

				_token_test_decrement_reference(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_DECREMENT_REFERENCE)) {}

				virtual ~_token_test_decrement_reference(void) {}

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

		} token_test_decrement_reference;

		typedef class _token_test_destroy :
				public test {
		
			public:

				_token_test_destroy(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_DESTROY)) {}

				virtual ~_token_test_destroy(void) {}

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

		} token_test_destroy;

		typedef class _token_test_get_reference_count :
				public test {
		
			public:

				_token_test_get_reference_count(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_GET_REFERENCE_COUNT)) {}

				virtual ~_token_test_get_reference_count(void) {}

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

		} token_test_get_reference_count;
	
		typedef class _token_test_get_token :
				public test {
		
			public:

				_token_test_get_token(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_GET_TOKEN)) {}

				virtual ~_token_test_get_token(void) {}

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

		} token_test_get_token;

		typedef class _token_test_increment_reference :
				public test {
		
			public:

				_token_test_increment_reference(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_INCREMENT_REFERENCE)) {}

				virtual ~_token_test_increment_reference(void) {}

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

		} token_test_increment_reference;

		typedef class _token_test_initialize :
				public test {
		
			public:

				_token_test_initialize(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_INITIALIZE)) {}

				virtual ~_token_test_initialize(void) {}

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

		} token_test_initialize;

		typedef class _token_test_is_registered :
				public test {
		
			public:

				_token_test_is_registered(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_IS_REGISTERED)) {}

				virtual ~_token_test_is_registered(void) {}

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

		} token_test_is_registered;

		typedef class _token_test_register_token :
				public test {
		
			public:

				_token_test_register_token(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_REGISTER_TOKEN)) {}

				virtual ~_token_test_register_token(void) {}

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

		} token_test_register_token;

		typedef class _token_test_registration_count :
				public test {
		
			public:

				_token_test_registration_count(void) :
					test(TOKEN_TEST_STRING(TOKEN_TEST_REGISTRATION_COUNT)) {}

				virtual ~_token_test_registration_count(void) {}

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

		} token_test_registration_count;
	}
}

#endif // TOKEN_TEST_H_
