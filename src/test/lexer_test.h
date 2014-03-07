/*
 * lexer_test.h
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

#ifndef LEXER_TEST_H_
#define LEXER_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		typedef enum {
			LEXER_TEST_CLEAR = 0,
			LEXER_TEST_DISCOVER,
			LEXER_TEST_GET_BEGIN_TOKEN_ID,
			LEXER_TEST_GET_END_TOKEN_ID,
			LEXER_TEST_ENUMERATE_ALPHA_TOKEN,
			LEXER_TEST_ENUMERATE_DIGIT_TOKEN,
			LEXER_TEST_ENUMERATE_STRING_TOKEN,
			LEXER_TEST_ENUMERATE_SYMBOL_TOKEN,
			LEXER_TEST_GET_TOKEN,
			LEXER_TEST_GET_TOKEN_ID,
			LEXER_TEST_GET_TOKEN_POSITION,
			LEXER_TEST_HAS_NEXT_TOKEN,
			LEXER_TEST_HAS_PREVIOUS_TOKEN,
			LEXER_TEST_MOVE_NEXT_TOKEN,
			LEXER_TEST_MOVE_PREVIOUS_TOKEN,
			LEXER_TEST_RESET,
			LEXER_TEST_SET,
			LEXER_TEST_SIZE,
		} lexer_test_type;

		static const std::string LEXER_TEST_STR[] = {
			"[Lexer] Clear",
			"[Lexer] Discover",
			"[Lexer] Get begin token id",
			"[Lexer] Get end token id",
			"[Lexer] Enumerate alpha token",
			"[Lexer] Enumerate digit token",
			"[Lexer] Enumerate string token",
			"[Lexer] Enumerate symbol token",
			"[Lexer] Get token",
			"[Lexer] Get token id",
			"[Lexer] Get token position",
			"[Lexer] Has next token",
			"[Lexer] Has previous token",
			"[Lexer] Move next token",
			"[Lexer] Move previous token",
			"[Lexer] Reset",
			"[Lexer] Set",
			"[Lexer] Size",
			};

		#define MAX_LEXER_TEST LEXER_TEST_SIZE
		#define LEXER_TEST_STRING(_TYPE_)\
			(((lexer_test_type) _TYPE_) > (lexer_test_type) MAX_LEXER_TEST ? UNKNOWN : LEXER_TEST_STR[_TYPE_])

		void lexer_register_tests(
			__inout test_suite &suite
			);

		typedef class _lexer_test_clear :
				public test {

			public:

				_lexer_test_clear(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_CLEAR)) {}

				virtual ~_lexer_test_clear(void) {}

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

		} lexer_test_clear;

		typedef class _lexer_test_discover :
				public test {

			public:

				_lexer_test_discover(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_DISCOVER)) {}

				virtual ~_lexer_test_discover(void) {}

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

		} lexer_test_discover;

		typedef class _lexer_test_get_begin_token_id :
				public test {

			public:

				_lexer_test_get_begin_token_id(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_GET_BEGIN_TOKEN_ID)) {}

				virtual ~_lexer_test_get_begin_token_id(void) {}

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

		} lexer_test_get_begin_token_id;

		typedef class _lexer_test_get_end_token_id :
				public test {

			public:

				_lexer_test_get_end_token_id(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_GET_END_TOKEN_ID)) {}

				virtual ~_lexer_test_get_end_token_id(void) {}

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

		} lexer_test_get_end_token_id;

		typedef class _lexer_test_enumerate_alpha_token :
				public test {

			public:

				_lexer_test_enumerate_alpha_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_ENUMERATE_ALPHA_TOKEN)) {}

				virtual ~_lexer_test_enumerate_alpha_token(void) {}

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

		} lexer_test_enumerate_alpha_token;

		typedef class _lexer_test_enumerate_digit_token :
				public test {

			public:

				_lexer_test_enumerate_digit_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_ENUMERATE_DIGIT_TOKEN)) {}

				virtual ~_lexer_test_enumerate_digit_token(void) {}

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

		} lexer_test_enumerate_digit_token;

		typedef class _lexer_test_enumerate_string_token :
				public test {

			public:

				_lexer_test_enumerate_string_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_ENUMERATE_STRING_TOKEN)) {}

				virtual ~_lexer_test_enumerate_string_token(void) {}

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

		} lexer_test_enumerate_string_token;

		typedef class _lexer_test_enumerate_symbol_token :
				public test {

			public:

				_lexer_test_enumerate_symbol_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_ENUMERATE_SYMBOL_TOKEN)) {}

				virtual ~_lexer_test_enumerate_symbol_token(void) {}

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

		} lexer_test_enumerate_symbol_token;

		typedef class _lexer_test_get_token :
				public test {

			public:

				_lexer_test_get_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_GET_TOKEN)) {}

				virtual ~_lexer_test_get_token(void) {}

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

		} lexer_test_get_token;

		typedef class _lexer_test_get_token_id :
				public test {

			public:

				_lexer_test_get_token_id(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_GET_TOKEN_ID)) {}

				virtual ~_lexer_test_get_token_id(void) {}

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

		} lexer_test_get_token_id;

		typedef class _lexer_test_get_token_position :
				public test {

			public:

				_lexer_test_get_token_position(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_GET_TOKEN_POSITION)) {}

				virtual ~_lexer_test_get_token_position(void) {}

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

		} lexer_test_get_token_position;

		typedef class _lexer_test_has_next_token :
				public test {

			public:

				_lexer_test_has_next_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_HAS_NEXT_TOKEN)) {}

				virtual ~_lexer_test_has_next_token(void) {}

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

		} lexer_test_has_next_token;

		typedef class _lexer_test_has_previous_token :
				public test {

			public:

				_lexer_test_has_previous_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_HAS_PREVIOUS_TOKEN)) {}

				virtual ~_lexer_test_has_previous_token(void) {}

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

		} lexer_test_has_previous_token;

		typedef class _lexer_test_move_next_token :
				public test {

			public:

				_lexer_test_move_next_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_MOVE_NEXT_TOKEN)) {}

				virtual ~_lexer_test_move_next_token(void) {}

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

		} lexer_test_move_next_token;

		typedef class _lexer_test_move_previous_token :
				public test {

			public:

				_lexer_test_move_previous_token(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_MOVE_PREVIOUS_TOKEN)) {}

				virtual ~_lexer_test_move_previous_token(void) {}

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

		} lexer_test_move_previous_token;

		typedef class _lexer_test_reset :
				public test {

			public:

				_lexer_test_reset(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_RESET)) {}

				virtual ~_lexer_test_reset(void) {}

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

		} lexer_test_reset;

		typedef class _lexer_test_set :
				public test {

			public:

				_lexer_test_set(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_SET)) {}

				virtual ~_lexer_test_set(void) {}

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

		} lexer_test_set;

		typedef class _lexer_test_size :
				public test {

			public:

				_lexer_test_size(void) : 
					test(LEXER_TEST_STRING(LEXER_TEST_SIZE)) {}

				virtual ~_lexer_test_size(void) {}

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

		} lexer_test_size;
	}
}

#endif // LEXER_TEST_H_
