/*
 * lexer_base_test.h
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

#ifndef LEXER_BASE_TEST_H_
#define LEXER_BASE_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
		
		typedef enum {
			LEXER_BASE_TEST_CLEAR = 0,
			LEXER_BASE_TEST_GET_CHARACTER,
			LEXER_BASE_TEST_GET_CHARACTER_COLUMN,
			LEXER_BASE_TEST_GET_CHARACTER_POSITION,
			LEXER_BASE_TEST_GET_CHARACTER_ROW,
			LEXER_BASE_TEST_GET_CHARACTER_TYPE,
			LEXER_BASE_TEST_GET_RAW_INPUT,
			LEXER_BASE_TEST_GET_SOURCE_PATH,
			LEXER_BASE_TEST_HAS_NEXT_CHARACTER,
			LEXER_BASE_TEST_HAS_PREVIOUS_CHARACTER,
			LEXER_BASE_TEST_INIT_WITH_FILE,
			LEXER_BASE_TEST_INIT_WITH_NON_FILE,
			LEXER_BASE_TEST_MOVE_NEXT_CHARACTER,
			LEXER_BASE_TEST_MOVE_PREVIOUS_CHARACTER,
			LEXER_BASE_TEST_RESET,
			LEXER_BASE_TEST_SIZE,
		} lexer_base_test_type;

		static const std::string LEXER_BASE_TEST_STR[] = {
			"[Lexer Base] Clear",
			"[Lexer Base] Get character",
			"[Lexer Base] Get character column",
			"[Lexer Base] Get character position",
			"[Lexer Base] Get character row",
			"[Lexer Base] Get character type",
			"[Lexer Base] Get raw input",
			"[Lexer Base] Get source path",
			"[Lexer Base] Has next character",
			"[Lexer Base] Has previous character",
			"[Lexer Base] Init with file",
			"[Lexer Base] Init with non-file",
			"[Lexer Base] Move next character",
			"[Lexer Base] Move previous character",
			"[Lexer Base] Reset",
			"[Lexer Base] Size",
			};

		#define MAX_LEXER_BASE_TEST LEXER_BASE_TEST_SIZE
		#define LEXER_BASE_TEST_STRING(_TYPE_)\
			(((lexer_base_test_type) _TYPE_) > (lexer_base_test_type) MAX_LEXER_BASE_TEST ? UNKNOWN : LEXER_BASE_TEST_STR[_TYPE_])

		void lexer_base_register_tests(
			__inout test_suite &suite
			);

		typedef class _lexer_base_test_clear :
				public test {

			public:

				_lexer_base_test_clear(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_CLEAR)) {}

				virtual ~_lexer_base_test_clear(void) {}

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

		} lexer_base_test_clear;

		typedef class _lexer_base_test_get_character :
				public test {

			public:

				_lexer_base_test_get_character(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_CHARACTER)) {}

				virtual ~_lexer_base_test_get_character(void) {}

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

		} lexer_base_test_get_character;

		typedef class _lexer_base_test_get_character_column :
				public test {

			public:

				_lexer_base_test_get_character_column(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_CHARACTER_COLUMN)) {}

				virtual ~_lexer_base_test_get_character_column(void) {}

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

		} lexer_base_test_get_character_column;

		typedef class _lexer_base_test_get_character_position :
				public test {

			public:

				_lexer_base_test_get_character_position(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_CHARACTER_POSITION)) {}

				virtual ~_lexer_base_test_get_character_position(void) {}

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

		} lexer_base_test_get_character_position;

		typedef class _lexer_base_test_get_character_row :
				public test {

			public:

				_lexer_base_test_get_character_row(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_CHARACTER_ROW)) {}

				virtual ~_lexer_base_test_get_character_row(void) {}

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

		} lexer_base_test_get_character_row;

		typedef class _lexer_base_test_get_character_type :
				public test {

			public:

				_lexer_base_test_get_character_type(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_CHARACTER_TYPE)) {}

				virtual ~_lexer_base_test_get_character_type(void) {}

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

		} lexer_base_test_get_character_type;

		typedef class _lexer_base_test_get_raw_input :
				public test {

			public:

				_lexer_base_test_get_raw_input(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_RAW_INPUT)) {}

				virtual ~_lexer_base_test_get_raw_input(void) {}

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

		} lexer_base_test_get_raw_input;

		typedef class _lexer_base_test_get_source_path :
				public test {

			public:

				_lexer_base_test_get_source_path(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_GET_SOURCE_PATH)) {}

				virtual ~_lexer_base_test_get_source_path(void) {}

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

		} lexer_base_test_get_source_path;

		typedef class _lexer_base_test_has_next_character :
				public test {

			public:

				_lexer_base_test_has_next_character(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_HAS_NEXT_CHARACTER)) {}

				virtual ~_lexer_base_test_has_next_character(void) {}

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

		} lexer_base_test_has_next_character;

		typedef class _lexer_base_test_has_previous_character :
				public test {

			public:

				_lexer_base_test_has_previous_character(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_HAS_PREVIOUS_CHARACTER)) {}

				virtual ~_lexer_base_test_has_previous_character(void) {}

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

		} lexer_base_test_has_previous_character;

		typedef class _lexer_base_test_init_with_file :
				public test {

			public:

				_lexer_base_test_init_with_file(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_INIT_WITH_FILE)) {}

				virtual ~_lexer_base_test_init_with_file(void) {}

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

		} lexer_base_test_init_with_file;

		typedef class _lexer_base_test_init_with_non_file :
				public test {

			public:

				_lexer_base_test_init_with_non_file(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_INIT_WITH_NON_FILE)) {}

				virtual ~_lexer_base_test_init_with_non_file(void) {}

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

		} lexer_base_test_init_with_non_file;

		typedef class _lexer_base_test_move_next_character :
				public test {

			public:

				_lexer_base_test_move_next_character(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_MOVE_NEXT_CHARACTER)) {}

				virtual ~_lexer_base_test_move_next_character(void) {}

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

		} lexer_base_test_move_next_character;

		typedef class _lexer_base_test_move_previous_character :
				public test {

			public:

				_lexer_base_test_move_previous_character(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_MOVE_PREVIOUS_CHARACTER)) {}

				virtual ~_lexer_base_test_move_previous_character(void) {}

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

		} lexer_base_test_move_previous_character;

		typedef class _lexer_base_test_reset :
				public test {

			public:

				_lexer_base_test_reset(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_RESET)) {}

				virtual ~_lexer_base_test_reset(void) {}

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

		} lexer_base_test_reset;

		typedef class _lexer_base_test_size :
				public test {

			public:

				_lexer_base_test_size(void) : 
					test(LEXER_BASE_TEST_STRING(LEXER_BASE_TEST_SIZE)) {}

				virtual ~_lexer_base_test_size(void) {}

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

		} lexer_base_test_size;
	}
}

#endif // LEXER_BASE_TEST_H_
