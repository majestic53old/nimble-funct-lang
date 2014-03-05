/*
 * token_tree_type.h
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

#ifndef TOKEN_TREE_TYPE_H_
#define TOKEN_TREE_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace COMPONENT_NS {
	
		namespace TOKEN_TREE_NS {
		
			typedef enum {
				TOKEN_TREE_EXCEPTION_ID_NOT_REGISTERED = 0,
				TOKEN_TREE_EXCEPTION_ID_NOT_VALID,
				TOKEN_TREE_EXCEPTION_UNINITIALIZED,
			} token_tree_exception_type;

			static const std::string TOKEN_TREE_EXCEPTION_STR[] = {
				"Token tree id is not registered",
				"Token tree id is not valid",
				"Token tree interface is uninitialized",
				};

			#define MAX_TOKEN_TREE_EXCEPTION_TYPE TOKEN_TREE_EXCEPTION_UNINITIALIZED
			#define TOKEN_TREE_HEADER "TOKEN_TREE"
			#define TOKEN_TREE_EXCEPTION_STRING(_TYPE_)\
				(((size_t) _TYPE_) > (size_t) MAX_TOKEN_TREE_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : TOKEN_TREE_EXCEPTION_STR[_TYPE_])
			#define THROW_TOKEN_TREE_EXCEPTION(_TYPE_)\
				THROW_INTERNAL_EXCEPTION(TOKEN_TREE_HEADER, TOKEN_TREE_EXCEPTION_STRING(_TYPE_))
			#define THROW_TOKEN_TREE_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
				THROW_INTERNAL_EXCEPTION_MESSAGE(TOKEN_TREE_HEADER, TOKEN_TREE_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)
		}
	}
}

#endif // TOKEN_TREE_TYPE_H_
