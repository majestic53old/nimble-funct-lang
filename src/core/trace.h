/*
 * trace.h
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

#ifndef TRACE_H_
#define TRACE_H_

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include "type.h"

namespace NIMBLE_NS {

	typedef enum {
		TRACE_FLAG_GENERIC = 0,
		TRACE_FLAG_COMPONENT,
		TRACE_FLAG_LEXER,
		TRACE_FLAG_LEXER_BASE,
		TRACE_FLAG_PARSER,
		TRACE_FLAG_TEST,
		TRACE_FLAG_TEST_SUITE,
		TRACE_FLAG_TOKEN,
		TRACE_FLAG_TOKEN_TREE,
		TRACE_FLAG_UNIQUE_ID,
		TRACE_FLAG_UNIQUE_ID_CLASS,
	} trace_flag;

	#ifndef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_GENERIC
	#endif // TRACE_FLAG

	typedef enum {
		TRACE_LEVEL_ERROR = 0,
		TRACE_LEVEL_INFORMATION,
		TRACE_LEVEL_VERBOSE,
	} trace_level;

	static const std::string TRACE_LEVEL_STR[] = {
		"ERROR",
		"INFORMATION",
		"VERBOSE",
		};

	#define MAX_TRACE_FLAG TRACE_FLAG_UNIQUE_ID_CLASS
	#define MAX_TRACE_LEVEL TRACE_LEVEL_VERBOSE
	#define SHOW_TRACE_FLAG TRACE_FLAG_GENERIC
	#define SHOW_TRACE_LEVEL TRACE_LEVEL_VERBOSE
	#define TRACE_LEVEL_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_TRACE_LEVEL ? UNKNOWN : TRACE_LEVEL_STR[_TYPE_])
#ifdef _WIN32
	#define TRACE_MESSAGE_OUTPUT(_STRING_) OutputDebugString(_STRING_);
#else
	#define TRACE_MESSAGE_OUTPUT(_STRING_) std::cout << _STRING_;
#endif // _WIN32
	#define TRACE_ENTRY_EXIT_BASE(_ENTRY_, _FORMAT_, ...) {\
		bool entry = _ENTRY_;\
		std::stringstream stream;\
		trace_level level = TRACE_LEVEL_VERBOSE;\
		trace_flag flag = TRACE_FLAG, show_flag = SHOW_TRACE_FLAG;\
		\
		if((show_flag == TRACE_FLAG_GENERIC) || (flag == show_flag)) {\
		\
			if(SHOW_TRACE_LEVEL >= level) {\
				stream << (entry ? FUNCT_ENTRY : FUNCT_EXIT) << format_as_string(_FORMAT_, __VA_ARGS__) << std::endl;\
				TRACE_MESSAGE_OUTPUT(stream.str().c_str());\
			}\
		}\
		}
	#define TRACE_MESSAGE_BASE(_LEVEL_, _VERBOSE_, _FORMAT_, ...) {\
		bool verbose = _VERBOSE_;\
		std::stringstream stream;\
		trace_level level = _LEVEL_;\
		trace_flag flag = TRACE_FLAG, show_flag = SHOW_TRACE_FLAG;\
		\
		if((show_flag == TRACE_FLAG_GENERIC) || (flag == show_flag)) {\
		\
			if(SHOW_TRACE_LEVEL >= level) {\
				stream << (verbose ? FUNCT_NAME_VERBOSE : FUNCT_NAME) << format_as_string(_FORMAT_, __VA_ARGS__) << std::endl;\
				TRACE_MESSAGE_OUTPUT(stream.str().c_str());\
			}\
		}\
		}
	#define _TRACE_ENTRY(_FORMAT_, ...) TRACE_ENTRY_EXIT_BASE(true, _FORMAT_, __VA_ARGS__)
	#define _TRACE_EXIT(_FORMAT_, ...) TRACE_ENTRY_EXIT_BASE(false, _FORMAT_, __VA_ARGS__)
	#define _TRACE_MESSAGE(_LEVEL_, _VERBOSE_, _FORMAT_, ...)\
		TRACE_MESSAGE_BASE(_LEVEL_, _VERBOSE_, _FORMAT_, __VA_ARGS__)
#ifdef _DEBUG
	#define TRACE_ENTRY() _TRACE_ENTRY(NULL)
	#define TRACE_ENTRY_MESSAGE(_FORMAT_, ...)\
		_TRACE_ENTRY(_FORMAT_, __VA_ARGS__)
	#define TRACE_EXIT() _TRACE_EXIT(NULL)
	#define TRACE_EXIT_MESSAGE(_FORMAT_, ...)\
		_TRACE_EXIT(_FORMAT_, __VA_ARGS__)
	#define TRACE_ERROR(_FORMAT_, ...)\
		_TRACE_MESSAGE(TRACE_LEVEL_ERROR, true, _FORMAT_, __VA_ARGS__)
	#define TRACE_INFORMATION(_FORMAT_, ...)\
		_TRACE_MESSAGE(TRACE_LEVEL_ERROR, true, _FORMAT_, __VA_ARGS__)
	#define TRACE_VERBOSE(_FORMAT_, ...)\
		_TRACE_MESSAGE(TRACE_LEVEL_ERROR, true, _FORMAT_, __VA_ARGS__)
#else
	#define TRACE_ENTRY()
	#define TRACE_ENTRY_MESSAGE(_FORMAT_, ...)
	#define TRACE_EXIT()
	#define TRACE_EXIT_MESSAGE(_FORMAT_, ...)
	#define TRACE_ERROR(_FORMAT_, ...)
	#define TRACE_INFORMATION(_FORMAT_, ...)
	#define TRACE_VERBOSE(_FORMAT_, ...)
#endif // _DEBUG
}

#endif // TRACE_H_
