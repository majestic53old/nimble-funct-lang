/*
 * lexer_type.h
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

#ifndef LEXER_TYPE_H_
#define LEXER_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
	
		typedef enum {
			LEXER_EXCEPTION_EXPECTING_IDENTIFIER = 0,
			LEXER_EXCEPTION_EXPECTING_NEXT_CHARACTER,
			LEXER_EXCEPTION_EXPECTING_PREVIOUS_CHARACTER,
			LEXER_EXCEPTION_EXPECTING_STRING,
			LEXER_EXCEPTION_EXPECTING_SYMBOL,
			LEXER_EXCEPTION_EXPECTING_TOKEN,
			LEXER_EXCEPTION_EXPECTING_VALUE,
			LEXER_EXCEPTION_INVALID_TOKEN_POSITION,
			LEXER_EXCEPTION_NO_NEXT_TOKEN,
			LEXER_EXCEPTION_NO_PREVIOUS_TOKEN,
			LEXER_EXCEPTION_UNTERMINATED_STRING,
			LEXER_EXCEPTION_UNTERMINATED_VALUE,
		} lexer_exception_type;

		static const std::string LEXER_EXCEPTION_STR[] = {
			"Expecting identifier type",
			"Expecting next character",
			"Expecting previous character",
			"Expecting string literal type",
			"Expecting symbol type",
			"Expecting token type",
			"Expecting value literal type",
			"Invalid token position",
			"No next token",
			"No previous token",
			"Unterminated string literal",
			"Unterminated value literal",
			};

		#define LEXER_HEADER "LEXER"
		#define MAX_LEXER_EXCEPTION_TYPE LEXER_EXCEPTION_UNTERMINATED_VALUE
		#define LEXER_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_LEXER_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : LEXER_EXCEPTION_STR[_TYPE_])
		#define THROW_LEXER_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(LEXER_HEADER, LEXER_EXCEPTION_STRING(_TYPE_))
		#define THROW_LEXER_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(LEXER_HEADER, LEXER_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _lexer;
		typedef _lexer lexer, *lexer_ptr;
	}
}

#endif // LEXER_TYPE_H_
