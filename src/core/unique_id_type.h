/*
 * unique_id_type.h
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

#ifndef UNIQUE_ID_TYPE_H_
#define UNIQUE_ID_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {
	
	namespace COMPONENT_NS {
	
		namespace UNIQUE_ID_NS {
		
			typedef enum {
				UNIQUE_ID_EXCEPTION_ID_IS_UNIQUE = 0,
				UNIQUE_ID_EXCEPTION_ID_NOT_REGISTERED,
				UNIQUE_ID_EXCEPTION_ID_NOT_VALID,
				UNIQUE_ID_EXCEPTION_UNINITIALIZED,
			} unique_id_exception_type;

			static const std::string UNIQUE_ID_EXCEPTION_STR[] = {
				"Unique id is marked as unique",
				"Unique id is not registered",
				"Unique id is not valid",
				"Unique id interface is uninitialized",
				};

			#define MAX_UNIQUE_ID_EXCEPTION_TYPE UNIQUE_ID_EXCEPTION_UNINITIALIZED
			#define UNIQUE_ID_HEADER "UNIQUE_ID"
			#define UNIQUE_ID_EXCEPTION_STRING(_TYPE_)\
				(((size_t) _TYPE_) > (size_t) MAX_UNIQUE_ID_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : UNIQUE_ID_EXCEPTION_STR[_TYPE_])
			#define THROW_UNIQUE_ID_EXCEPTION(_TYPE_)\
				THROW_INTERNAL_EXCEPTION(UNIQUE_ID_HEADER, UNIQUE_ID_EXCEPTION_STRING(_TYPE_))
			#define THROW_UNIQUE_ID_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
				THROW_INTERNAL_EXCEPTION_MESSAGE(UNIQUE_ID_HEADER, UNIQUE_ID_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)
		}
	}
}

#endif
