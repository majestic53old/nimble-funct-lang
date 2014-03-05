/*
 * component_type.h
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

#ifndef COMPONENT_TYPE_H_
#define COMPONENT_TYPE_H_

#include "exception.h"

namespace NIMBLE_NS {

	namespace COMPONENT_NS {
		
		typedef enum {
			COMPONENT_EXCEPTION_UNINITIALIZED = 0,
		} component_exception_type;

		static const std::string COMPONENT_EXCEPTION_STR[] = {
			"Component interface is uninitialized",
			};

		#define COMPONENT_HEADER "COMPONENT"
		#define MAX_COMPONENT_EXCEPTION_TYPE COMPONENT_EXCEPTION_UNINITIALIZED
		#define COMPONENT_EXCEPTION_STRING(_TYPE_)\
			(((size_t) _TYPE_) > (size_t) MAX_COMPONENT_EXCEPTION_TYPE ? UNKNOWN_EXCEPTION : COMPONENT_EXCEPTION_STR[_TYPE_])
		#define THROW_COMPONENT_EXCEPTION(_TYPE_)\
			THROW_INTERNAL_EXCEPTION(COMPONENT_HEADER, COMPONENT_EXCEPTION_STRING(_TYPE_))
		#define THROW_COMPONENT_EXCEPTION_MESSAGE(_TYPE_, _FORMAT_, ...)\
			THROW_INTERNAL_EXCEPTION_MESSAGE(COMPONENT_HEADER, COMPONENT_EXCEPTION_STRING(_TYPE_), _FORMAT_, __VA_ARGS__)
	}
}

#endif // COMPONENT_TYPE_H_
