/*
 * parser_type.h
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

#ifndef PARSER_TYPE_H_
#define PARSER_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
	
		typedef enum {
			PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS = 0,
			PARSER_EXCEPTION_EXPECTING_CONDITIONAL,
			PARSER_EXCEPTION_EXPECTING_DIRECTIVE,
			PARSER_EXCEPTION_EXPECTING_EXPRESSION,
			PARSER_EXCEPTION_EXPECTING_EXPRESSION_LIST,
			PARSER_EXCEPTION_EXPECTING_FUNCTION_CALL,
			PARSER_EXCEPTION_EXPECTING_FUNCTION_DEFINITION,
			PARSER_EXCEPTION_EXPECTING_IDENTIFIER,
			PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST,
			PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_PARAMETERS,
			PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_RESULT,
			PARSER_EXCEPTION_EXPECTING_LIST_OPERATOR,
			PARSER_EXCEPTION_EXPECTING_LITERAL_VALUE,
			PARSER_EXCEPTION_EXPECTING_NEXT_TOKEN,
			PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS,
			PARSER_EXCEPTION_EXPECTING_OPERATOR,
			PARSER_EXCEPTION_EXPECTING_PREVIOUS_TOKEN,
			PARSER_EXCEPTION_EXPECTING_SWITCH_CASE,
			PARSER_EXCEPTION_INVALID_STATEMENT_POSITION,
			PARSER_EXCEPTION_NO_NEXT_STATEMENT,
			PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT,
			PARSER_EXCEPTION_UNKNOWN_CONDITIONAL,
			PARSER_EXCEPTION_UNKNOWN_DIRECTIVE,
			PARSER_EXCEPTION_UNKNOWN_FUNCTION_CALL,
			PARSER_EXCEPTION_UNKNOWN_LIST_OPERATOR,
		} parser_exception_type;

		static const std::string PARSER_EXCEPTION_STR[] = {
			"Expecting closing parethesis",
			"Expecting conditional",
			"Expecting directive",
			"Expecting expression",
			"Expecting expression list",
			"Expecting function call",
			"Expecting function definition",
			"Expecting identifier",
			"Expecting identifier list",
			"Expecting identifier list parameters",
			"Expecting identifier list result",
			"Expecting list operator",
			"Expecting literal value",
			"Expecting next token",
			"Expecting opening parethesis",
			"Expecting operator",
			"Expecting previous token",
			"Expecting switch case",
			"Invalid statement position",
			"No next statement",
			"No previous statement",
			"Unknown conditional",
			"Unknown directive",
			"Unknown function call",
			"Unknown list operator",
			};

		#define MAX_PARSER_EXCEPTION_TYPE PARSER_EXCEPTION_UNKNOWN_LIST_OPERATOR
		#define PARSER_HEADER "PARSER"
		#define PARSER_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_PARSER_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : PARSER_EXCEPTION_STR[_TYPE_])
		#define THROW_PARSER_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(PARSER_HEADER, PARSER_EXCEPTION_STRING(_TYPE_))
		#define THROW_PARSER_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(PARSER_HEADER, PARSER_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _parser;
		typedef _parser parser, *parser_ptr;
	}
}

#endif // PARSER_TYPE_H_
