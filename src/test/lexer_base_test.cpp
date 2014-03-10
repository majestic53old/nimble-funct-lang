/*
 * lexer_base_test.cpp
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
#include "lexer_base.h"
#include "lexer_base_test.h"
#include "test_type.h"
#include "trace.h"

namespace NIMBLE_NS {

	namespace TEST_NS {

		#define LEXER_BASE_TEST_FILE_PATH "..\\..\\..\\test\\file_test.nb"
		#define LEXER_BASE_TEST_INPUT "; Nimble test file\n; *** DO NOT MODIFY ***\n;test\n(testinput);345\n123(\t(()\n"
		#define LEXER_BASE_TEST_INPUT_LENGTH std::string(LEXER_BASE_TEST_INPUT).size()

		static lexer_base_test_clear lexer_base_test_0;
		static lexer_base_test_get_character lexer_base_test_1;
		static lexer_base_test_get_character_column lexer_base_test_2;
		static lexer_base_test_get_character_position lexer_base_test_3;
		static lexer_base_test_get_character_row lexer_base_test_4;
		static lexer_base_test_get_character_type lexer_base_test_5;
		static lexer_base_test_get_raw_input lexer_base_test_6;
		static lexer_base_test_get_source_path lexer_base_test_7;
		static lexer_base_test_has_next_character lexer_base_test_8;
		static lexer_base_test_has_previous_character lexer_base_test_9;
		static lexer_base_test_init_with_file lexer_base_test_10;
		static lexer_base_test_init_with_non_file lexer_base_test_11;
		static lexer_base_test_move_next_character lexer_base_test_12;
		static lexer_base_test_move_previous_character lexer_base_test_13;
		static lexer_base_test_reset lexer_base_test_14;
		static lexer_base_test_size lexer_base_test_15;

		void 
		lexer_base_register_tests(
			__inout test_suite &suite
			)
		{
			TRACE_ENTRY();

			suite.register_test(lexer_base_test_0);
			suite.register_test(lexer_base_test_1);
			suite.register_test(lexer_base_test_2);
			suite.register_test(lexer_base_test_3);
			suite.register_test(lexer_base_test_4);
			suite.register_test(lexer_base_test_5);
			suite.register_test(lexer_base_test_6);
			suite.register_test(lexer_base_test_7);
			suite.register_test(lexer_base_test_8);
			suite.register_test(lexer_base_test_9);
			suite.register_test(lexer_base_test_10);
			suite.register_test(lexer_base_test_11);
			suite.register_test(lexer_base_test_12);
			suite.register_test(lexer_base_test_13);
			suite.register_test(lexer_base_test_14);
			suite.register_test(lexer_base_test_15);

			TRACE_EXIT();
		}

		test_result 
		_lexer_base_test_clear::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				lex_base.clear();
				result = ((lex_base.get_character() != CHARACTER_EOS) 
					|| (lex_base.get_character_type() != CHARACTER_TYPE_SYMBOL) 
					|| (lex_base.get_raw_input().size() != 1)
					|| !lex_base.get_source_path().empty()
					|| lex_base.get_character_column()
					|| lex_base.get_character_position()
					|| lex_base.get_character_row()) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_clear::setup_test(
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
		_lexer_base_test_clear::teardown_test(
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
		_lexer_base_test_get_character::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t iter = 0;
			char current_character;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				current_character = lex_base.get_character();

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
					
					if(current_character != lex_base.get_character(iter)) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {
						current_character = lex_base.move_next_character();
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
		_lexer_base_test_get_character::setup_test(
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
		_lexer_base_test_get_character::teardown_test(
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
		_lexer_base_test_get_character_column::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			char current_character;
			size_t iter = 0, column = 0;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				current_character = lex_base.get_character();

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
				
					if(column != lex_base.get_character_column()) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {

						if(current_character == CHARACTER_NEWLINE) {
							column = 0;
						} else {
							++column;
						}

						current_character = lex_base.move_next_character();
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
		_lexer_base_test_get_character_column::setup_test(
			__in uintptr_t context ,
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
		_lexer_base_test_get_character_column::teardown_test(
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
		_lexer_base_test_get_character_position::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t iter = 0;
			char current_character;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				current_character = lex_base.get_character();

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
				
					if(iter != lex_base.get_character_position()) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {
						current_character = lex_base.move_next_character();
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
		_lexer_base_test_get_character_position::setup_test(
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
		_lexer_base_test_get_character_position::teardown_test(
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
		_lexer_base_test_get_character_row::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			char current_character;
			size_t iter = 0, row = 0;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				current_character = lex_base.get_character();

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
				
					if(row != lex_base.get_character_row()) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {

						if(current_character == CHARACTER_NEWLINE) {
							++row;
						}

						current_character = lex_base.move_next_character();
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
		_lexer_base_test_get_character_row::setup_test(
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
		_lexer_base_test_get_character_row::teardown_test(
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
		_lexer_base_test_get_character_type::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t iter = 0;
			char current_character;
			character_type current_type;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
					current_type = CHARACTER_TYPE_SYMBOL;
					current_character = lex_base.get_character();

					if(isalpha(current_character)) {
						current_type = CHARACTER_TYPE_ALPHA;
					} else if(isdigit(current_character)) {
						current_type = CHARACTER_TYPE_DIGIT;
					} else if(isspace(current_character)) {
						current_type = CHARACTER_TYPE_WHITESPACE;
					}

					if(lex_base.get_character_type() != current_type) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {
						lex_base.move_next_character();
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
		_lexer_base_test_get_character_type::setup_test(
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
		_lexer_base_test_get_character_type::teardown_test(
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
		_lexer_base_test_get_raw_input::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t iter = 0;
			std::string raw_input;
			char current_character;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				raw_input = lex_base.get_raw_input();

				for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
					current_character = lex_base.get_character();

					if(raw_input.at(iter) != current_character) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					try {
						lex_base.move_next_character();
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
		_lexer_base_test_get_raw_input::setup_test(
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
		_lexer_base_test_get_raw_input::teardown_test(
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
		_lexer_base_test_get_source_path::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				
				if(!lex_base.get_source_path().empty()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_FILE_PATH);
				result = (lex_base.get_source_path() != std::string(LEXER_BASE_TEST_FILE_PATH)) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_get_source_path::setup_test(
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
		_lexer_base_test_get_source_path::teardown_test(
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
		_lexer_base_test_has_next_character::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				result = !lex_base.has_next_character() ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;

				try {

					while(lex_base.has_next_character()) {
						lex_base.move_next_character();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = ((lex_base.get_character_position() != LEXER_BASE_TEST_INPUT_LENGTH)
					|| (lex_base.has_next_character())) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_has_next_character::setup_test(
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
		_lexer_base_test_has_next_character::teardown_test(
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
		_lexer_base_test_has_previous_character::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t iter = 0;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				result = lex_base.has_previous_character() ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;

				if(result == TEST_RESULT_SUCCESS) {
					
					for(; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
						lex_base.move_next_character();
					}
				}

				try {

					while(lex_base.has_previous_character()) {
						lex_base.move_previous_character();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = lex_base.get_character_position() ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_has_previous_character::setup_test(
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
		_lexer_base_test_has_previous_character::teardown_test(
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
		_lexer_base_test_init_with_file::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			std::string expected_input;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			expected_input = LEXER_BASE_TEST_INPUT;
			expected_input += CHARACTER_EOS;

			try {

				try {
					lex_base = LANGUAGE_NS::lexer_base(".");
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {
					result = TEST_RESULT_SUCCESS;
				}

				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_FILE_PATH);
				result = ((lex_base.get_raw_input() != expected_input) 
					|| (lex_base.get_raw_input().size() != (LEXER_BASE_TEST_INPUT_LENGTH + 1))) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_init_with_file::setup_test(
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
		_lexer_base_test_init_with_file::teardown_test(
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
		_lexer_base_test_init_with_non_file::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			std::string expected_input;
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			expected_input = LEXER_BASE_TEST_INPUT;
			expected_input += CHARACTER_EOS;

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				result = ((lex_base.get_raw_input() != expected_input) 
					|| (lex_base.get_raw_input().size() != (LEXER_BASE_TEST_INPUT_LENGTH + 1))) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_init_with_non_file::setup_test(
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
		_lexer_base_test_init_with_non_file::teardown_test(
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
		_lexer_base_test_move_next_character::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			LANGUAGE_NS::lexer_base lex_base;
			size_t current_position, iter = 0;
			char current_character, initial_character;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				initial_character = lex_base.get_character();
				current_position = lex_base.get_character_position();

				try {
					
					for(iter; iter < LEXER_BASE_TEST_INPUT_LENGTH; ++iter) {
						
						if(current_position != iter) {
							TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
							result = TEST_RESULT_FAILURE;
							goto exit;
						}

						current_character = lex_base.move_next_character();
						current_position = lex_base.get_character_position();
					}

					result = TEST_RESULT_SUCCESS;
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}
				
				try {
					lex_base.move_next_character();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {
					result = TEST_RESULT_SUCCESS;
				}
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
		_lexer_base_test_move_next_character::setup_test(
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
		_lexer_base_test_move_next_character::teardown_test(
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
		_lexer_base_test_move_previous_character::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{	
			int32_t iter, random_action;
			LANGUAGE_NS::lexer_base lex_base;
			char current_character, initial_character;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				current_character = lex_base.get_character();
				initial_character = current_character;
				random_action = (std::rand() % (LEXER_BASE_TEST_INPUT_LENGTH - 1)) + 1;

				try {
					lex_base.move_previous_character();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {
					result = TEST_RESULT_SUCCESS;
				}

				for(iter = 0; iter < random_action; ++iter) {
					current_character = lex_base.move_next_character();
				}

				for(iter = 0; iter < random_action; ++iter) {
					current_character = lex_base.move_previous_character();
				}

				result = ((current_character != initial_character) 
					|| (lex_base.get_character() != initial_character)
					|| (lex_base.get_character_position())) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_move_previous_character::setup_test(
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
		_lexer_base_test_move_previous_character::teardown_test(
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
		_lexer_base_test_reset::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			int32_t rand_action;
			char initial_character;
			LANGUAGE_NS::lexer_base lex_base;
			character_type initial_character_type;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				result = TEST_RESULT_SUCCESS;
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				initial_character = lex_base.get_character();
				initial_character_type = lex_base.get_character_type();
				rand_action = std::rand() % LEXER_BASE_TEST_INPUT_LENGTH;
				
				while(rand_action-- > 0) {

					if(!lex_base.has_next_character()) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}

					lex_base.move_next_character();
				}

				lex_base.reset();
				result = ((lex_base.get_character_position() != 0)
					|| (lex_base.get_character() != initial_character)
					|| (lex_base.get_character_type() != initial_character_type)) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_reset::setup_test(
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
		_lexer_base_test_reset::teardown_test(
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
		_lexer_base_test_size::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			LANGUAGE_NS::lexer_base lex_base;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				lex_base = LANGUAGE_NS::lexer_base(LEXER_BASE_TEST_INPUT, false);
				result = (lex_base.size() != (LEXER_BASE_TEST_INPUT_LENGTH + 1)) ? TEST_RESULT_FAILURE : TEST_RESULT_SUCCESS;
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
		_lexer_base_test_size::setup_test(
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
		_lexer_base_test_size::teardown_test(
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
