/*
 * main.cpp
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

#include "code_generator.h"
#include "component.h"
#include "component_test.h"
#include "lexer_test.h"
#include "lexer_base_test.h"
#include "parser.h"
#include "parser_test.h"
#include "token_test.h"
#include "token_tree_test.h"
#include "unique_id_test.h"
#include "unique_id_class_test.h"
#include "version.h"

using namespace NIMBLE_NS;
using namespace TEST_NS;

typedef enum {
	LAYER_LEXER = 0,
	LAYER_LEXER_BASE,
	LAYER_PARSER,
	LAYER_CODE_GENERATOR,
} layer_type;

static const std::string LAYER_TYPE_STR[] = {
	"LEXER", "LEXER_BASE", "PARSER", "CODE_GENERATOR",
	};

#define MAX_LAYER_TYPE LAYER_CODE_GENERATOR
#define LAYER_TYPE_STRING(_TYPE_)\
	(((size_t) (_TYPE_)) > (size_t) MAX_LAYER_TYPE ? UNKNOWN : LAYER_TYPE_STR[_TYPE_])

/*
 * Test configuration
 */
//#define UNIT_TEST_MODE
#ifdef UNIT_TEST_MODE
#define SHOW_ONLY_FAILURES_MODE true
#define VERBOSE_MODE true
#else
#define RUN_LAYER ((layer_type) LAYER_PARSER)
#define SOURCE_INPUT "..\\..\\..\\test\\file_test2.nb"
#define SOURCE_IS_FILE true
#define VERBOSE_MODE true
#endif // UNIT_TEST_MODE

#ifndef UNIT_TEST_MODE
bool 
allocate_layer(
	__in const layer_type &layer,
	__out LANGUAGE_NS::lexer_base_ptr &lex_base,
	__out LANGUAGE_NS::lexer_ptr &lex,
	__out LANGUAGE_NS::parser_ptr &par,
	__in const std::string &input = std::string(),
	__in bool is_file = false
	)
{
	bool result = true;

	switch(layer) {
		case LAYER_LEXER:
			lex_base = new LANGUAGE_NS::lexer(input, is_file);
			lex = (LANGUAGE_NS::lexer_ptr) lex_base;

			if(!lex_base || !lex) {
				result = false;
			}
			break;
		case LAYER_LEXER_BASE:
			lex_base = new LANGUAGE_NS::lexer_base(input, is_file);

			if(!lex_base) {
				result = false;
			}
			break;
		case LAYER_PARSER:
			lex_base = new LANGUAGE_NS::parser(input, is_file);
			par = (LANGUAGE_NS::parser_ptr) lex_base;

			if(!lex_base || !par) {
				result = false;
			}
			break;
		case LAYER_CODE_GENERATOR:

			// TODO: ...

			break;
		default:
			result = false;
			break;
	}

	return result;
}

bool 
deallocate_layer(
	__in const layer_type &layer,
	__out LANGUAGE_NS::lexer_ptr &lex,
	__out LANGUAGE_NS::parser_ptr &par,
	__out LANGUAGE_NS::lexer_base_ptr &lex_base
	)
{
	bool result = true;

	if(lex_base) {

		switch(layer) {
			case LAYER_LEXER:

				if(lex) {
					delete lex;
					lex = NULL;
				} else {
					result = false;
				}
				break;
			case LAYER_LEXER_BASE:

				if(lex_base) {
					delete lex_base;
				} else {
					result = false;
				}
				break;
			case LAYER_PARSER:

				if(par) {
					delete par;
					par = NULL;
				} else {
					result = false;
				}
				break;
			case LAYER_CODE_GENERATOR:

				// TODO: ...

				break;
		}

		lex_base = NULL;
	}

	return result;
}

bool 
run_layer(
	__in const layer_type &layer,
	__in const std::string &input,
	__in bool is_file = false,
	__in bool verbose = false,
	__in bool traverse_previous = false
	)
{
	bool result = true, running;
	LANGUAGE_NS::lexer_ptr lex = NULL;
	LANGUAGE_NS::parser_ptr par = NULL;
	LANGUAGE_NS::lexer_base_ptr lex_base = NULL;

	std::cout << "[" << LAYER_TYPE_STRING(layer) << " LAYER]" << std::endl << "---" << std::endl;

	result = allocate_layer(layer, lex_base, lex, par, input, is_file);

	if(result) {
		running = true;

		while(running) {

			switch(layer) {
				case LAYER_LEXER:
					running = lex->has_next_token();
					std::cout << lex->to_string(verbose) << std::endl;

					if(running) {
						lex->move_next_token();
					}
					break;
				case LAYER_LEXER_BASE:
					running = lex_base->has_next_character();
					std::cout << lex_base->to_string(verbose) << std::endl;

					if(running) {
						lex_base->move_next_character();
					}
					break;
				case LAYER_PARSER:
					running = par->has_next_statement();
					std::cout << par->to_string(verbose) << std::endl;

					if(running) {
						par->move_next_statement();
					}
					break;
				case LAYER_CODE_GENERATOR:

					// TODO: ...

					break;
				default:
					running = false;
					result = false;
					break;
			}
		}
	}

	if(result && traverse_previous) {
		running = true;

		while(running) {

			switch(layer) {
				case LAYER_LEXER:
					running = lex->has_previous_token();
					
					if(running) {
						lex->move_previous_token();
						std::cout << lex->to_string(verbose) << std::endl;
					}
					break;
				case LAYER_LEXER_BASE:
					running = lex_base->has_previous_character();

					if(running) {
						lex_base->move_previous_character();
						std::cout << lex_base->to_string(verbose) << std::endl;
					}
					break;
				case LAYER_PARSER:
					running = par->has_previous_statement();
					
					if(running) {
						par->move_previous_statement();
						std::cout << par->to_string(verbose) << std::endl;
					}
					break;
				case LAYER_CODE_GENERATOR:

					// TODO: ...

					break;
				default:
					running = false;
					result = false;
					break;
			}
		}
	}

	result = deallocate_layer(layer, lex, par, lex_base);

	return result;
}
#else

void 
run_tests(
	__in bool show_only_failures = false,
	__in bool verbose = false
	)
{
	test_suite suite;
	
	std::cout << "[RUNNING TESTS]" << std::endl << "---" << std::endl;
	component_register_tests(suite);
	lexer_register_tests(suite);
	lexer_base_register_tests(suite);
	parser_register_tests(suite);
	token_register_tests(suite);
	token_tree_register_tests(suite);
	unique_id_register_tests(suite);
	unique_id_class_register_tests(suite);
	suite.run_all_tests();
	std::cout << suite.to_string(show_only_failures, verbose) << std::endl;
}
#endif // UNIT_TEST_MODE

int
main(void) 
{
	int result = 0;

	std::cout << library_version(true, true, true) << std::endl << "---" << std::endl;

	try {
#ifdef UNIT_TEST_MODE
		run_tests(SHOW_ONLY_FAILURES_MODE, VERBOSE_MODE);
#else
		COMPONENT_NS::initialize();

		if(!run_layer(RUN_LAYER, SOURCE_INPUT, SOURCE_IS_FILE, VERBOSE_MODE)) {
			std::cerr << "Failed to run layer: " << LAYER_TYPE_STRING(RUN_LAYER) << std::endl;
			result = 1;
		}

		COMPONENT_NS::destroy();
#endif // UNIT_TEST_MODE
	} catch(std::runtime_error &exc) {
		std::cerr << exc.what() << std::endl;
		result = 1;
	}

	std::cin.get();

	return result;
}
