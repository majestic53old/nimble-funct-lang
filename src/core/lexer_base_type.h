/*
 * lexer_base_type.h
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

#ifndef LEXER_BASE_TYPE_H_
#define LEXER_BASE_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
		
		typedef enum {
			LEXER_BASE_EXCEPTION_FILE_NOT_FOUND = 0,
			LEXER_BASE_EXCEPTION_INVALID_CHARACTER_COLUMN,
			LEXER_BASE_EXCEPTION_INVALID_CHARACTER_POSITION,
			LEXER_BASE_EXCEPTION_NO_NEXT_CHARACTER,
			LEXER_BASE_EXCEPTION_NO_PREVIOUS_CHARACTER,
			LEXER_BASE_EXCEPTION_UNKNOWN_CHARACTER_TYPE,
		} lexer_base_exception;

		static const std::string LEXER_BASE_EXCEPTION_STR[] = {
			"File not found",
			"Invalid character column",
			"Invalid character position",
			"No next character",
			"No previous character",
			"Unknown character type",
			};
		
		#define LEXER_BASE_HEADER "LEXER_BASE"
		#define MAX_LEXER_BASE_EXCEPTION_TYPE LEXER_BASE_EXCEPTION_UNKNOWN_CHARACTER_TYPE
		#define LEXER_BASE_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_LEXER_BASE_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : LEXER_BASE_EXCEPTION_STR[_TYPE_])
		#define THROW_LEXER_BASE_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(LEXER_BASE_HEADER, LEXER_BASE_EXCEPTION_STRING(_TYPE_))
		#define THROW_LEXER_BASE_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(LEXER_BASE_HEADER, LEXER_BASE_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _lexer_base;
		typedef _lexer_base lexer_base, *lexer_base_ptr;
	}
}

#endif // LEXER_BASE_TYPE_H_
