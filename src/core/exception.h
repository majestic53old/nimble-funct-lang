/*
 * exception.h
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

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <stdexcept>
#include "type.h"

namespace NIMBLE_NS {

	typedef enum {
		EXCEPTION_TYPE_INTERNAL = 0,
		EXCEPTION_TYPE_UNKNOWN,
	} exception_type;

	static const std::string EXCEPTION_TYPE_STR[] = {
		"INTERNAL_EXCEPTION",
		"UNKNOWN_EXCEPTION",
		};

	#define EXCEPTION_HEADER NIMBLE_NS
	#define MAX_EXCEPTION_TYPE EXCEPTION_TYPE_UNKNOWN
	#define UNKNOWN_EXCEPTION "Unknown exception"
	#define EXCEPTION_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_EXCEPTION_TYPE ? EXCEPTION_TYPE_STR[EXCEPTION_TYPE_UNKNOWN] : EXCEPTION_TYPE_STR[_TYPE_])
#ifdef _DEBUG
	#define EXCEPTION_MESSAGE_OUTPUT(_HEADER_, _TYPE_)\
		"[" << _HEADER_ << "::" << EXCEPTION_TYPE_STRING(_TYPE_) << " => " << FUNCT_NAME_VERBOSE << "] "
#else
	#define EXCEPTION_MESSAGE_OUTPUT(_HEADER_, _TYPE_) std::string()
#endif // _DEBUG
	#define THROW_EXCEPTION_BASE(_TYPE_, _HEADER_, _EXCEPTION_) {\
		std::stringstream stream;\
		\
		stream << EXCEPTION_MESSAGE_OUTPUT(_HEADER_, _TYPE_) << _EXCEPTION_;\
		throw std::runtime_error(stream.str().c_str());\
		}
	#define THROW_EXCEPTION_MESSAGE_BASE(_TYPE_, _HEADER_, _EXCEPTION_, _FORMAT_, ...) {\
		std::stringstream stream;\
		const char *format = _FORMAT_;\
		\
		stream << EXCEPTION_MESSAGE_OUTPUT(_HEADER_, _TYPE_) << _EXCEPTION_;\
		\
		if(format) {\
			stream << format_as_string(format, __VA_ARGS__);\
		}\
		throw std::runtime_error(stream.str().c_str());\
		}
	#define THROW_INTERNAL_EXCEPTION(_HEADER_, _EXCEP_)\
		THROW_EXCEPTION_BASE(EXCEPTION_TYPE_INTERNAL, _HEADER_, _EXCEP_)
	#define THROW_UNKNOWN_EXCEPTION(_HEADER_, _EXCEP_)\
		THROW_EXCEPTION_BASE(EXCEPTION_TYPE_UNKNOWN, _HEADER_, _EXCEP_)
	#define THROW_INTERNAL_EXCEPTION_MESSAGE(_HEADER_, _EXCEP_, _FORMAT_, ...)\
		THROW_EXCEPTION_MESSAGE_BASE(EXCEPTION_TYPE_INTERNAL, _HEADER_, _EXCEP_, _FORMAT_, __VA_ARGS__)
	#define THROW_UNKNOWN_EXCEPTION_MESSAGE(_HEADER_, _EXCEP_, _FORMAT_, ...)\
		THROW_EXCEPTION_MESSAGE_BASE(EXCEPTION_TYPE_UNKNOWN, _HEADER_, _EXCEP_, _FORMAT_, __VA_ARGS__)
}

#endif // EXCEPTION_H_
