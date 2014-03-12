/*
 * parser_test.cpp
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

#include "component.h"
#include "parser.h"
#include "parser_test.h"
#include "test.h"
#include "test_type.h"
#include "token.h"
#include "token_tree.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	namespace TEST_NS {

		#define PARSER_TEST_FILE_PATH "..\\..\\..\\test\\file_test2.nb"
		#define PARSER_TEST_INPUT "; Nimble test file\n; *** DO NOT MODIFY ***\n;;;;;;;;;;;;;;;; MATH ;;;;;;;;;;;;;;;;\n(\n\tdef \
			(abs) num (result num)\n\t(\n\t\tif (< result 0) (set result (* result ~1))\n\t)\n)\n(\n\tdef (sqrt) num (result)\n\t(\
			\n\t\t(set result (call sqrt_helper num (call abs (* num 0.5)) 0.00001))\n\t)\n)\n(\n\tdef (sqrt_helper) orig next tolerance \
			(result orig)\n\t(\n\t\tif (< next tolerance) return \n\t\t(\n\t\t\twhile (> (call abs (- (* (+ (/ orig result) result) 0.5) \
			result)) tolerance) \n\t\t\t(\t\t\t\t(set result next)\n\t\t\t)\n\t\t)\n\t)\n)\n;;;;;;;;;;;;;;;; PRIME ;;;;;;;;;;;;;;;;\n(\n\tdef \
			(is_prime) num (result false)\n\t(\n\t\tif (< num 2) return \n\t\t(\n\t\t\t(set result (call is_prime_helper num (call sqrt num)))\
			\n\t\t)\n\t)\n)\n(\n\tdef (is_prime_helper) num max (result true)\n\t(\n\t\twhile (> max 2) if (= (% num (postdec max)) 0) (set result \
			false) \n\t\t(\n\t\t\tif (= result false) break\n\t\t)\n\t)\n)\n;;;;;;;;;;;;;;;; MAIN ;;;;;;;;;;;;;;;;\n(\n\tprint (call is_prime \
			0)\n)\n(\n\tprint (call is_prime 2)\n)\n(\n\tprint (call is_prime ~1)\n)\n(\n\tprint (call is_prime 5)\n)"
		#define PARSER_TEST_INPUT_LENGTH std::string(PARSER_TEST_INPUT).size()

		typedef enum {
			CONDITIONAL_TEST_IF = 0,
			CONDITIONAL_TEST_IF_ELSE,
			CONDITIONAL_TEST_SWITCH,
			CONDITIONAL_TEST_SWITCH_ELSE,
			CONDITIONAL_WHILE,
		} conditional_test_type;

		static const std::string CONDITIONAL_TEST_STR[] = {
			"(if (< a 5) (set b 5))",
			"(if (< a 5) (set b 5) ((set b a)))",
			"(switch a 0 (set b a) 5 (set b a))",
			"(switch a 0 (set b a) 5 (set b a) else (set b 5))",
			"(while (< a 5) (preinc a))",
			};

		#define MAX_CONDITIONAL_TEST CONDITIONAL_WHILE
		#define CONDITIONAL_TEST_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_CONDITIONAL_TEST ? UNKNOWN : CONDITIONAL_TEST_STR[_TYPE_])

		typedef enum {
			DIRECTIVE_TEST_BREAK = 0,
			DIRECTIVE_TEST_CONTINUE,
			DIRECTIVE_TEST_RETURN,
		} directive_test_type;

		static const std::string DIRECTIVE_TEST_STR[] = {
			"(break)", "(continue)", "(return)",
			};

		#define MAX_DIRECTIVE_TEST DIRECTIVE_TEST_RETURN
		#define DIRECTIVE_TEST_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_DIRECTIVE_TEST ? UNKNOWN : DIRECTIVE_TEST_STR[_TYPE_])

		typedef enum {
			EXPRESSION_TEST_FUNCTION_CALL = 0,
			EXPRESSION_TEST_FUNCTION_CALL_WITH_PARAMETERS,
			EXPRESSION_TEST_FUNCTION_POSTDEC,
			EXPRESSION_TEST_FUNCTION_POSTINC,
			EXPRESSION_TEST_FUNCTION_PREDEC,
			EXPRESSION_TEST_FUNCTION_PREINC,
			EXPRESSION_TEST_FUNCTION_PRINT,
			EXPRESSION_TEST_FUNCTION_SET,
			EXPRESSION_TEST_FUNCTION_UNDEF,
			EXPRESSION_TEST_LIST_OPERATOR_BEGIN,
			EXPRESSION_TEST_LIST_OPERATOR_END,
			EXPRESSION_TEST_LIST_OPERATOR_POP,
			EXPRESSION_TEST_LIST_OPERATOR_PUSH,
			EXPRESSION_TEST_LITERAL_FALSE,
			EXPRESSION_TEST_LITERAL_FALSE_NEGATIVE,
			EXPRESSION_TEST_LITERAL_FLOAT,
			EXPRESSION_TEST_LITERAL_FLOAT_NEGATIVE,
			EXPRESSION_TEST_LITERAL_IDENTIFIER,
			EXPRESSION_TEST_LITERAL_IDENTIFIER_NEGATIVE,
			EXPRESSION_TEST_LITERAL_INTEGER,
			EXPRESSION_TEST_LITERAL_INTEGER_NEGATIVE,
			EXPRESSION_TEST_LITERAL_STRING,
			EXPRESSION_TEST_LITERAL_TRUE,
			EXPRESSION_TEST_LITERAL_TRUE_NEGATIVE,
			EXPRESSION_TEST_NESTED,
			EXPRESSION_TEST_OPERATOR_AND,
			EXPRESSION_TEST_OPERATOR_DIVIDE,
			EXPRESSION_TEST_OPERATOR_EQUALS,
			EXPRESSION_TEST_OPERATOR_GREATER_THEN,
			EXPRESSION_TEST_OPERATOR_LESS_THEN,
			EXPRESSION_TEST_OPERATOR_MODULUS,
			EXPRESSION_TEST_OPERATOR_MULTIPLY,
			EXPRESSION_TEST_OPERATOR_NOT_EQUALS,
			EXPRESSION_TEST_OPERATOR_OR,
			EXPRESSION_TEST_OPERATOR_PLUS,
			EXPRESSION_TEST_OPERATOR_SUBTRACT,
			EXPRESSION_TEST_OPERATOR_XOR,
		} expression_test_type;

		static const std::string EXPRESSION_TEST_STR[] = {
			"(call f)", "(call f a (+ b 34) (* c d))", "(postdec a)", "(postinc a)", "(predec a)",
			"(preinc a)", "(print a)", "(set a (+ 3 4))", "(undef a)", "(begin lst)", "(end lst)",
			"(pop lst)", "(push lst (+ 3 4))", "(set a false)", "(set a ~false)", "(set a 3.14159)",
			"(set a ~3.14159)", "(set a b)", "(set a ~b)", "(set a 3)", "(set a ~3)", "(set a \"str\")",
			"(set a true)", "(set a ~true)", "(* (+ 3 4) (- 54 35))", "(& 3 4)", "(/ 3 4)", "(= 3 4)",
			"(> 3 4)", "(< 3 4)", "(% 3 4)", "(* 3 4)", "(! 3 4)", "(| 3 4)", "(+ 3 4)", "(- 3 4)", 
			"(^ 3 4)",
			};

		#define MAX_EXPRESSION_TEST EXPRESSION_TEST_OPERATOR_XOR
		#define EXPRESSION_TEST_STRING(_TYPE_)\
			(((size_t) _TYPE_) > MAX_EXPRESSION_TEST ? UNKNOWN : EXPRESSION_TEST_STR[_TYPE_])

		typedef enum {
			FUNCTION_DEFINITION_TEST_NO_PARAMETERS,
			FUNCTION_DEFINITION_TEST_PARAMETERS_RETURN_SET,
			FUNCTION_DEFINITION_TEST_PARAMETERS_RETURN_UNSET,
		} function_definition_test_type;

		static const std::string FUNCTION_DEFINITION_TEST_STR[] = {
			"(def (f) ( return ))",
			"(def (f) a b ( result true ) ( return ))",
			"(def (f) a b ( result ) ( return ))",
			};

		#define MAX_FUNCTION_DEFINITION_TEST FUNCTION_DEFINITION_TEST_PARAMETERS_RETURN_UNSET
		#define FUNCTION_DEFINITION_TEST_STRING(_TYPE_)\
			(((size_t) _TYPE_) > MAX_FUNCTION_DEFINITION_TEST ? UNKNOWN : FUNCTION_DEFINITION_TEST_STR[_TYPE_])

		static parser_test_clear parser_test_0;
		static parser_test_discover parser_test_1;
		static parser_test_enumerate_conditional parser_test_2;
		static parser_test_enumerate_directive parser_test_3;
		static parser_test_enumerate_expression parser_test_4;
		static parser_test_enumerate_function_definition parser_test_5;
		static parser_test_get_statement parser_test_6;
		static parser_test_get_statement_id parser_test_7;
		static parser_test_get_statement_position parser_test_8;
		static parser_test_has_next_statement parser_test_9;
		static parser_test_has_previous_statement parser_test_10;
		static parser_test_move_next_statement parser_test_11;
		static parser_test_move_previous_statement parser_test_12;
		static parser_test_reset parser_test_13;
		static parser_test_set parser_test_14;
		static parser_test_size parser_test_15;


		void 
		parser_register_tests(
			__inout test_suite &suite
			)
		{
			TRACE_ENTRY();

			suite.register_test(parser_test_0);
			suite.register_test(parser_test_1);
			suite.register_test(parser_test_2);
			suite.register_test(parser_test_3);
			suite.register_test(parser_test_4);
			suite.register_test(parser_test_5);
			suite.register_test(parser_test_6);
			suite.register_test(parser_test_7);
			suite.register_test(parser_test_8);
			suite.register_test(parser_test_9);
			suite.register_test(parser_test_10);
			suite.register_test(parser_test_11);
			suite.register_test(parser_test_12);
			suite.register_test(parser_test_13);
			suite.register_test(parser_test_14);
			suite.register_test(parser_test_15);

			TRACE_EXIT();
		}

		test_result 
		_parser_test_clear::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);

				while(par.has_next_statement()) {
					par.move_next_statement();
				}

				par.clear();

				if(par.get_statement_position()
						|| (par.get_statement().id != par.get_begin_token_id())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_clear::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_clear::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_discover::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false), par2(PARSER_TEST_FILE_PATH);

				par2.discover();

				while(par.has_next_statement()) {
					par.move_next_statement();
				}

				if(par2.size() != par.size()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_discover::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_discover::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_enumerate_conditional::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t type = CONDITIONAL_TEST_IF;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
			
				for(; type <= MAX_CONDITIONAL_TEST; ++type) {
					LANGUAGE_NS::parser par(CONDITIONAL_TEST_STRING(type), false);
					par.discover();
					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_enumerate_conditional::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_enumerate_conditional::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_enumerate_directive::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t type = DIRECTIVE_TEST_BREAK;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
			
				for(; type <= MAX_DIRECTIVE_TEST; ++type) {
					LANGUAGE_NS::parser par(DIRECTIVE_TEST_STRING(type), false);
					par.discover();
					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_enumerate_directive::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_enumerate_directive::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_enumerate_expression::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t type = EXPRESSION_TEST_FUNCTION_CALL;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				for(; type <= MAX_EXPRESSION_TEST; ++type) {
					LANGUAGE_NS::parser par(EXPRESSION_TEST_STRING(type), false);
					par.discover();
					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_enumerate_expression::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_enumerate_expression::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_enumerate_function_definition::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t type = FUNCTION_DEFINITION_TEST_NO_PARAMETERS;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				for(; type <= MAX_FUNCTION_DEFINITION_TEST; ++type) {
					LANGUAGE_NS::parser par(FUNCTION_DEFINITION_TEST_STRING(type), false);
					par.discover();
					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_enumerate_function_definition::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_enumerate_function_definition::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_get_statement::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t position = 0;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
				
				while(par.has_next_statement()) {
					
					if(par.get_statement() != par.get_statement(position++)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_get_statement::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_get_statement::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_get_statement_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				while(par.has_next_statement()) {

					if(!COMPONENT_NS::TOKEN_TREE_NS::is_registered(par.get_statement_id())) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_get_statement_id::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_get_statement_id::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_get_statement_position::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t position = 0;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				while(par.has_next_statement()) {
					
					if(par.get_statement_position() != position++) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					par.move_next_statement();
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_get_statement_position::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_get_statement_position::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_has_next_statement::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				while(par.has_next_statement()) {
					par.move_next_statement();
				}

				if(par.has_next_statement()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				par.reset();

				if(!par.has_next_statement()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_has_next_statement::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_has_next_statement::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_has_previous_statement::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				if(par.has_previous_statement()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(par.has_next_statement()) {
					par.move_next_statement();
				}

				if(!par.has_previous_statement()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(par.has_previous_statement()) {
					par.move_previous_statement();	
				}

				if(par.has_previous_statement()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_has_previous_statement::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_has_previous_statement::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_move_next_statement::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				try {

					while(par.has_next_statement()) {
						par.move_next_statement();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				try {
					par.move_next_statement();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_move_next_statement::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_move_next_statement::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_move_previous_statement::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				try {
					par.move_previous_statement();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				while(par.has_next_statement()) {
					par.move_next_statement();
				}

				try {
					
					if(par.has_previous_statement()) {
						par.move_previous_statement();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_move_previous_statement::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_move_previous_statement::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_reset::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				par.move_next_statement();
				par.reset();

				if(par.get_statement_position()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_reset::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_reset::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_set::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false), par2 = par,
					par3 = LANGUAGE_NS::parser(PARSER_TEST_FILE_PATH);

				par.discover();
				par2.discover();
				par3.discover();

				while(par.has_next_statement()) {
					
					if(COMPONENT_NS::TOKEN_NS::get_token(par.get_statement().id) 
							!= COMPONENT_NS::TOKEN_NS::get_token(par2.get_statement().id)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					if(COMPONENT_NS::TOKEN_NS::get_token(par.get_statement().id) 
							!= COMPONENT_NS::TOKEN_NS::get_token(par3.get_statement().id)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					par.move_next_statement();

					try {
						par2.move_next_statement();
						par3.move_next_statement();
					} catch(...) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_set::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_set::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_parser_test_size::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::parser par(PARSER_TEST_INPUT, false);
			
				par.discover();

				if(!par.size()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				par.clear();

				if(par.size()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_parser_test_size::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_parser_test_size::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}
	}
}
