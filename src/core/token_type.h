/*
 * token_type.h
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

#ifndef TOKEN_TYPE_H_
#define TOKEN_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace COMPONENT_NS {

		namespace TOKEN_NS {

			typedef enum {
				TOKEN_EXCEPTION_ID_NOT_REGISTERED = 0,
				TOKEN_EXCEPTION_ID_NOT_VALID,
				TOKEN_EXCEPTION_UNINITIALIZED,
			} token_exception_type;

			static const std::string TOKEN_EXCEPTION_STR[] = {
				"Token id is not registered",
				"Token id is not valid",
				"Token interface is uninitialized",
				};

			#define MAX_TOKEN_EXCEPTION_TYPE TOKEN_EXCEPTION_UNINITIALIZED
			#define TOKEN_HEADER "TOKEN"
			#define TOKEN_EXCEPTION_STRING(_TYPE_)\
				(((size_t) _TYPE_) > (size_t) MAX_TOKEN_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : TOKEN_EXCEPTION_STR[_TYPE_])
			#define THROW_TOKEN_EXCEPTION(_TYPE_)\
				THROW_INTERNAL_EXCEPTION(TOKEN_HEADER, TOKEN_EXCEPTION_STRING(_TYPE_))
			#define THROW_TOKEN_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
				THROW_INTERNAL_EXCEPTION_MESSAGE(TOKEN_HEADER, TOKEN_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)
		}
	}
}

#endif // TOKEN_TYPE_H_
