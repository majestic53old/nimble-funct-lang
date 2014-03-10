/*
 * lexer_test.cpp
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
#include "lexer.h"
#include "lexer_test.h"
#include "lexer_type.h"
#include "test.h"
#include "test_type.h"
#include "token.h"
#include "trace.h"

namespace NIMBLE_NS {

	namespace TEST_NS {

		#define LEXER_TEST_FILE_PATH "..\\..\\..\\test\\file_test.nb"
		#define LEXER_TEST_INPUT ";test\n(testinput);345\n123(\t(()\n"
		#define LEXER_TEST_INPUT_LENGTH std::string(LEXER_TEST_INPUT).size()

		static const std::string lexer_test_alpha_input[] = {
			"alpha", "_alpha_", "a__lpha", "zvcbdwegsd",
			};

		static const std::string lexer_test_int_input[] = {
			"10", "12345", "0000", "0234",
			};

		static const std::string lexer_test_float_input[] = {
			"0.3", "234.34", "34.5", "432.45678",
			};

		static const std::string lexer_test_string_input[] = {
			"\"\"", "\"abc\"", "\"___dsfadfsdf342.652\"", "\"3457642_++=234=\"",
			};

		static const std::string lexer_test_symbol_input[] = {
			"((()))", "+-*", "***", "/%"
			};

		#define MAX_LEXER_TEST_INPUT (4)

		static lexer_test_clear lexer_test_0;
		static lexer_test_discover lexer_test_1;
		static lexer_test_get_begin_token_id lexer_test_2;
		static lexer_test_get_end_token_id lexer_test_3;
		static lexer_test_enumerate_alpha_token lexer_test_4;
		static lexer_test_enumerate_digit_token lexer_test_5;
		static lexer_test_enumerate_string_token lexer_test_6;
		static lexer_test_enumerate_symbol_token lexer_test_7;
		static lexer_test_get_token lexer_test_8;
		static lexer_test_get_token_id lexer_test_9;
		static lexer_test_get_token_position lexer_test_10;
		static lexer_test_has_next_token lexer_test_11;
		static lexer_test_has_previous_token lexer_test_12;
		static lexer_test_move_next_token lexer_test_13;
		static lexer_test_move_previous_token lexer_test_14;
		static lexer_test_reset lexer_test_15;
		static lexer_test_set lexer_test_16;
		static lexer_test_size lexer_test_17;

		void 
		lexer_register_tests(
			__inout test_suite &suite
			)
		{
			TRACE_ENTRY();

			suite.register_test(lexer_test_0);
			suite.register_test(lexer_test_1);
			suite.register_test(lexer_test_2);
			suite.register_test(lexer_test_3);
			suite.register_test(lexer_test_4);
			suite.register_test(lexer_test_5);
			suite.register_test(lexer_test_6);
			suite.register_test(lexer_test_7);
			suite.register_test(lexer_test_8);
			suite.register_test(lexer_test_9);
			suite.register_test(lexer_test_10);
			suite.register_test(lexer_test_11);
			suite.register_test(lexer_test_12);
			suite.register_test(lexer_test_13);
			suite.register_test(lexer_test_14);
			suite.register_test(lexer_test_15);
			suite.register_test(lexer_test_16);
			suite.register_test(lexer_test_17);

			TRACE_EXIT();
		}

		test_result 
		_lexer_test_clear::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);
				lex.discover();

				if(!lex.size()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				lex.clear();

				if(lex.get_token_position() || lex.size()) {
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
		_lexer_test_clear::setup_test(
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
		_lexer_test_clear::teardown_test(
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
		_lexer_test_discover::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);
				lex.discover();

				if(!lex.size()) {
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
		_lexer_test_discover::setup_test(
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
		_lexer_test_discover::teardown_test(
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
		_lexer_test_get_begin_token_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				if((COMPONENT_NS::TOKEN_NS::get_token(lex.get_begin_token_id()).type != TOKEN_TYPE_BEGIN)
						|| (COMPONENT_NS::TOKEN_NS::get_token(lex2.get_begin_token_id()).type != TOKEN_TYPE_BEGIN)) {
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
		_lexer_test_get_begin_token_id::setup_test(
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
		_lexer_test_get_begin_token_id::teardown_test(
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
		_lexer_test_get_end_token_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				if((COMPONENT_NS::TOKEN_NS::get_token(lex.get_end_token_id()).type != TOKEN_TYPE_END)
						|| (COMPONENT_NS::TOKEN_NS::get_token(lex2.get_end_token_id()).type != TOKEN_TYPE_END)) {
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
		_lexer_test_get_end_token_id::setup_test(
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
		_lexer_test_get_end_token_id::teardown_test(
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
		_lexer_test_enumerate_alpha_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t i = 0;
			token_type type;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				for(; i < MAX_LEXER_TEST_INPUT; ++i) {
					LANGUAGE_NS::lexer lex(lexer_test_alpha_input[i], false);
					lex.move_next_token();

					while(lex.has_next_token()) {
						type = lex.get_token().type;

						if((type != TOKEN_TYPE_CONDITIONAL)
								&& (type != TOKEN_TYPE_CONSTANT)
								&& (type != TOKEN_TYPE_DIRECTIVE)
								&& (type != TOKEN_TYPE_FUNCTION)
								&& (type != TOKEN_TYPE_IDENTIFIER)
								&& (type != TOKEN_TYPE_LIST_OPERATOR)) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						lex.move_next_token();
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
		_lexer_test_enumerate_alpha_token::setup_test(
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
		_lexer_test_enumerate_alpha_token::teardown_test(
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
		_lexer_test_enumerate_digit_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t i;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				for(i = 0; i < MAX_LEXER_TEST_INPUT; ++i) {
					LANGUAGE_NS::lexer lex(lexer_test_int_input[i], false);
					lex.move_next_token();

					while(lex.has_next_token()) {
						
						if(lex.get_token().type != TOKEN_TYPE_VALUE_LITERAL) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						lex.move_next_token();
					}
				}

				for(i = 0; i < MAX_LEXER_TEST_INPUT; ++i) {
					LANGUAGE_NS::lexer lex(lexer_test_float_input[i], false);
					lex.move_next_token();

					while(lex.has_next_token()) {
						
						if(lex.get_token().type != TOKEN_TYPE_VALUE_LITERAL) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						lex.move_next_token();
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
		_lexer_test_enumerate_digit_token::setup_test(
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
		_lexer_test_enumerate_digit_token::teardown_test(
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
		_lexer_test_enumerate_string_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t i = 0;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				for(; i < MAX_LEXER_TEST_INPUT; ++i) {
					LANGUAGE_NS::lexer lex(lexer_test_string_input[i], false);
					lex.move_next_token();

					while(lex.has_next_token()) {
						
						if(lex.get_token().type != TOKEN_TYPE_STRING_LITERAL) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						lex.move_next_token();
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
		_lexer_test_enumerate_string_token::setup_test(
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
		_lexer_test_enumerate_string_token::teardown_test(
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
		_lexer_test_enumerate_symbol_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t i = 0;
			token_type type;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				for(; i < MAX_LEXER_TEST_INPUT; ++i) {
					LANGUAGE_NS::lexer lex(lexer_test_symbol_input[i], false);
					lex.move_next_token();

					while(lex.has_next_token()) {
						type = lex.get_token().type;

						if((type != TOKEN_TYPE_SYMBOL)
								&& (type != TOKEN_TYPE_OPERATOR)) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						lex.move_next_token();
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
		_lexer_test_enumerate_symbol_token::setup_test(
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
		_lexer_test_enumerate_symbol_token::teardown_test(
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
		_lexer_test_get_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			token tok;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);

				while(lex.has_next_token()) {
					tok = lex.get_token();

					if(tok != COMPONENT_NS::TOKEN_NS::get_token(lex.get_token_id())) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					lex.move_next_token();
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
		_lexer_test_get_token::setup_test(
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
		_lexer_test_get_token::teardown_test(
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
		_lexer_test_get_token_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid tok_id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);

				while(lex.has_next_token()) {
					tok_id = lex.get_token_id();

					if(lex.get_token() != COMPONENT_NS::TOKEN_NS::get_token(tok_id)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					lex.move_next_token();
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
		_lexer_test_get_token_id::setup_test(
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
		_lexer_test_get_token_id::teardown_test(
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
		_lexer_test_get_token_position::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t pos = 0;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);

				while(lex.has_next_token()) {
					
					if(lex.get_token_position() != pos) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					lex.move_next_token();
					++pos;
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
		_lexer_test_get_token_position::setup_test(
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
		_lexer_test_get_token_position::teardown_test(
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
		_lexer_test_has_next_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				lex.move_next_token();

				if(lex.has_next_token()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(!lex2.has_next_token()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(lex2.has_next_token()) {
					lex2.move_next_token();
				}

				if(lex2.has_next_token()) {
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
		_lexer_test_has_next_token::setup_test(
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
		_lexer_test_has_next_token::teardown_test(
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
		_lexer_test_has_previous_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				if(lex.has_previous_token()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(lex2.has_next_token()) {
					lex2.move_next_token();
				}

				if(lex2.has_next_token()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(lex2.has_previous_token()) {
					lex2.move_previous_token();
				}

				if(lex2.get_token_position()) {
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
		_lexer_test_has_previous_token::setup_test(
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
		_lexer_test_has_previous_token::teardown_test(
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
		_lexer_test_move_next_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				lex.move_next_token();

				try {
					lex.move_next_token();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					lex2.move_next_token();
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
		_lexer_test_move_next_token::setup_test(
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
		_lexer_test_move_next_token::teardown_test(
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
		_lexer_test_move_previous_token::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false);

				try {
					lex.move_previous_token();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				while(lex2.has_next_token()) {
					lex2.move_next_token();
				}

				try {
					lex2.move_previous_token();
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
		_lexer_test_move_previous_token::setup_test(
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
		_lexer_test_move_previous_token::teardown_test(
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
		_lexer_test_reset::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			token tok;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex(LEXER_TEST_INPUT, false);

				tok = lex.get_token();

				while(lex.has_next_token()) {
					lex.move_next_token();
				}

				lex.reset();

				if((lex.get_token_position() != 0)
						|| (lex.get_token() != tok)) {
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
		_lexer_test_reset::setup_test(
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
		_lexer_test_reset::teardown_test(
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
		_lexer_test_set::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false), lex3(LEXER_TEST_FILE_PATH);

				if((lex.get_token_position() != 0)
						|| (lex2.get_token_position() != 0)
						|| (lex3.get_token_position() != 0)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				lex.move_next_token();

				if(lex.has_next_token()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				while(lex2.has_next_token()) {

					if(!lex3.has_next_token()
							|| (lex2.get_token().subtype != lex3.get_token().subtype)
							|| (lex2.get_token().text != lex3.get_token().text)
							|| (lex2.get_token().type != lex3.get_token().type)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					lex2.move_next_token();
					lex3.move_next_token();
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
		_lexer_test_set::setup_test(
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
		_lexer_test_set::teardown_test(
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
		_lexer_test_size::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				LANGUAGE_NS::lexer lex, lex2(LEXER_TEST_INPUT, false), lex3(LEXER_TEST_FILE_PATH);

				lex.discover();
				lex2.discover();
				lex3.discover();

				if(lex.size()
						|| (!lex2.size())
						|| (!lex3.size())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				lex3.clear();

				if(lex3.size()) {
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
		_lexer_test_size::setup_test(
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
		_lexer_test_size::teardown_test(
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
