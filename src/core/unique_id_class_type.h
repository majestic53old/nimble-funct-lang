/*
 * unique_id_class_type.h
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

#ifndef UNIQUE_ID_CLASS_TYPE_H_
#define UNIQUE_ID_CLASS_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace COMPONENT_NS {
		
		typedef enum {
			UNIQUE_ID_CLASS_EXCEPTION_UNIQUE_ID_ASSIGNMENT = 0,
		} unique_id_class_exception_type;

		static const std::string UNIQUE_ID_CLASS_EXCEPTION_STR[] = {
			"Unique id in assignment",
			};

		#define MAX_UNIQUE_ID_CLASS_EXCEPTION UNIQUE_ID_CLASS_EXCEPTION_UNIQUE_ID_ASSIGNMENT
		#define UNIQUE_ID_CLASS_HEADER "UNIQUE_ID_CLASS"
		#define UNIQUE_ID_CLASS_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_UNIQUE_ID_CLASS_EXCEPTION ? UNKNOWN_EXCEPTION : UNIQUE_ID_CLASS_EXCEPTION_STR[_TYPE_])
		#define THROW_UNIQUE_ID_CLASS_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(UNIQUE_ID_CLASS_HEADER, UNIQUE_ID_CLASS_EXCEPTION_STRING(_TYPE_))
		#define THROW_UNIQUE_ID_CLASS_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(UNIQUE_ID_CLASS_HEADER, UNIQUE_ID_CLASS_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)

		class _unique_id_class;
		typedef _unique_id_class unique_id_class, *unique_id_class_ptr;
	}
}

#endif // UNIQUE_ID_CLASS_TYPE_H_
