/*
 * code_generator_type.h
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

#ifndef CODE_GENERATOR_TYPE_H_
#define CODE_GENERATOR_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
		
		typedef enum {
			CODE_GENERATOR_EXCEPTION_EXPECTING_STATEMENT_LIST = 0,
		} code_generator_exception;

		static const std::string CODE_GENERATOR_EXCEPTION_STR[] = {
			"Expecting statement list",
			};

		#define CODE_GENERATOR_HEADER "CODE_GENERATOR"
		#define MAX_CODE_GENERATOR_EXCEPTION CODE_GENERATOR_EXCEPTION_EXPECTING_STATEMENT_LIST
		#define CODE_GENERATOR_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > MAX_CODE_GENERATOR_EXCEPTION ? UNKNOWN_EXCEPTION : CODE_GENERATOR_EXCEPTION_STR[_TYPE_])
		#define THROW_CODE_GENERATOR_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(CODE_GENERATOR_HEADER, CODE_GENERATOR_EXCEPTION_STRING(_TYPE_))
		#define THROW_CODE_GENERATOR_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(CODE_GENERATOR_HEADER, CODE_GENERATOR_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _code_generator;
		typedef _code_generator code_generator, *code_generator_ptr;
	}
}

#endif // CODE_GENERATOR_TYPE_H_
