/*
 * parser_test.h
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

#ifndef PARSER_TEST_H_
#define PARSER_TEST_H_

#include "test_suite.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
		
		typedef enum {
			PARSER_TEST_CLEAR = 0,
			PARSER_TEST_DISCOVER,
			PARSER_TEST_ENUMERATE_CONDITIONAL,
			PARSER_TEST_ENUMERATE_DIRECTIVE,
			PARSER_TEST_ENUMERATE_EXPRESSION,
			PARSER_TEST_ENUMERATE_FUNCTION_DEFINITION,
			PARSER_TEST_GET_STATEMENT,
			PARSER_TEST_GET_STATEMENT_ID,
			PARSER_TEST_GET_STATEMENT_POSITION,
			PARSER_TEST_HAS_NEXT_STATEMENT,
			PARSER_TEST_HAS_PREVIOUS_STATEMENT,
			PARSER_TEST_MOVE_NEXT_STATEMENT,
			PARSER_TEST_MOVE_PREVIOUS_STATEMENT,
			PARSER_TEST_RESET,
			PARSER_TEST_SET,
			PARSER_TEST_SIZE,
		} parser_test_type;

		static const std::string PARSER_TEST_STR[] = {
			"[Parser] Clear",
			"[Parser] Discover",
			"[Parser] Enumerate conditional",
			"[Parser] Enumerate directive",
			"[Parser] Enumerate expression",
			"[Parser] Enumerate function definition",
			"[Parser] Get statement",
			"[Parser] Get statement Id",
			"[Parser] Get statement position",
			"[Parser] Has next statement",
			"[Parser] Has previous statement",
			"[Parser] Move next statement",
			"[Parser] Move previous statement",
			"[Parser] Reset",
			"[Parser] Set",
			"[Parser] Size",
			};

		#define MAX_PARSER_TEST PARSER_TEST_SIZE
		#define PARSER_TEST_STRING(_TYPE_)\
			(((parser_test_type) _TYPE_) > (parser_test_type) MAX_PARSER_TEST ? UNKNOWN : PARSER_TEST_STR[_TYPE_])

		void parser_register_tests(
			__inout test_suite &suite
			);

		typedef class _parser_test_clear :
				public test {
		
			public:

				_parser_test_clear(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_CLEAR)) {}

				virtual ~_parser_test_clear(void) {}

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

		} parser_test_clear;

		typedef class _parser_test_discover :
				public test {
		
			public:

				_parser_test_discover(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_DISCOVER)) {}

				virtual ~_parser_test_discover(void) {}

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

		} parser_test_discover;

		typedef class _parser_test_enumerate_conditional :
				public test {
		
			public:

				_parser_test_enumerate_conditional(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_ENUMERATE_CONDITIONAL)) {}

				virtual ~_parser_test_enumerate_conditional(void) {}

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

		} parser_test_enumerate_conditional;

		typedef class _parser_test_enumerate_directive :
				public test {
		
			public:

				_parser_test_enumerate_directive(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_ENUMERATE_DIRECTIVE)) {}

				virtual ~_parser_test_enumerate_directive(void) {}

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

		} parser_test_enumerate_directive;

		typedef class _parser_test_enumerate_expression :
				public test {
		
			public:

				_parser_test_enumerate_expression(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_ENUMERATE_EXPRESSION)) {}

				virtual ~_parser_test_enumerate_expression(void) {}

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

		} parser_test_enumerate_expression;

		typedef class _parser_test_enumerate_function_definition :
				public test {
		
			public:

				_parser_test_enumerate_function_definition(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_ENUMERATE_FUNCTION_DEFINITION)) {}

				virtual ~_parser_test_enumerate_function_definition(void) {}

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

		} parser_test_enumerate_function_definition;

		typedef class _parser_test_get_statement :
				public test {
		
			public:

				_parser_test_get_statement(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_GET_STATEMENT)) {}

				virtual ~_parser_test_get_statement(void) {}

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

		} parser_test_get_statement;

		typedef class _parser_test_get_statement_id :
				public test {
		
			public:

				_parser_test_get_statement_id(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_GET_STATEMENT_ID)) {}

				virtual ~_parser_test_get_statement_id(void) {}

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

		} parser_test_get_statement_id;

		typedef class _parser_test_get_statement_position :
				public test {
		
			public:

				_parser_test_get_statement_position(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_GET_STATEMENT_POSITION)) {}

				virtual ~_parser_test_get_statement_position(void) {}

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

		} parser_test_get_statement_position;

		typedef class _parser_test_has_next_statement :
				public test {
		
			public:

				_parser_test_has_next_statement(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_HAS_NEXT_STATEMENT)) {}

				virtual ~_parser_test_has_next_statement(void) {}

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

		} parser_test_has_next_statement;

		typedef class _parser_test_has_previous_statement :
				public test {
		
			public:

				_parser_test_has_previous_statement(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_HAS_PREVIOUS_STATEMENT)) {}

				virtual ~_parser_test_has_previous_statement(void) {}

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

		} parser_test_has_previous_statement;

		typedef class _parser_test_move_next_statement :
				public test {
		
			public:

				_parser_test_move_next_statement(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_MOVE_NEXT_STATEMENT)) {}

				virtual ~_parser_test_move_next_statement(void) {}

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

		} parser_test_move_next_statement;

		typedef class _parser_test_move_previous_statement :
				public test {
		
			public:

				_parser_test_move_previous_statement(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_MOVE_PREVIOUS_STATEMENT)) {}

				virtual ~_parser_test_move_previous_statement(void) {}

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

		} parser_test_move_previous_statement;

		typedef class _parser_test_reset :
				public test {
		
			public:

				_parser_test_reset(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_RESET)) {}

				virtual ~_parser_test_reset(void) {}

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

		} parser_test_reset;

		typedef class _parser_test_set :
				public test {
		
			public:

				_parser_test_set(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_SET)) {}

				virtual ~_parser_test_set(void) {}

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

		} parser_test_set;

		typedef class _parser_test_size :
				public test {
		
			public:

				_parser_test_size(void) :
					test(PARSER_TEST_STRING(PARSER_TEST_SIZE)) {}

				virtual ~_parser_test_size(void) {}

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

		} parser_test_size;
	}
}

#endif // PARSER_TEST_H_
