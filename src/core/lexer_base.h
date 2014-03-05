/*
 * lexer_base.h
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

#ifndef LEXER_BASE_H_
#define LEXER_BASE_H_

#include <map>
#include "type.h"

namespace NIMBLE_NS {

	#ifndef LANGUAGE_NS
	#define LANGUAGE_NS language
	#endif // LANGUAGE_NS

	namespace LANGUAGE_NS {
	
		typedef class _lexer_base {
		
			public:

				_lexer_base(void);

				_lexer_base(
					__in const std::string &input,
					__in_opt size_t is_file = true
					);

				_lexer_base(
					__in const _lexer_base &other
					);

				virtual ~_lexer_base(void);

				_lexer_base &operator=(
					__in const _lexer_base &other
					);

				virtual void clear(void);

				static character_type determine_character_type(
					__in char character
					);

				char get_character(void);

				char get_character(
					__in size_t position
					);

				size_t get_character_column(void);

				size_t get_character_position(void);

				size_t get_character_row(void);

				character_type get_character_type(void);

				std::string &get_raw_input(void);

				std::string get_source_path(void);

				bool has_next_character(void);

				bool has_previous_character(void);

				bool has_source_path(void);

				char move_next_character(void);

				char move_previous_character(void);

				virtual void reset(void);

				virtual void set(
					__in const std::string &input,
					__in_opt size_t is_file = true
					);

				virtual size_t size(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				size_t m_character_column;

				std::map<size_t, size_t> m_character_column_length;

				size_t m_character_position;

				size_t m_character_row;

				character_type m_character_type;

				std::string m_raw_input;

				std::string m_source_path;

			private:

				std::recursive_mutex m_lexer_base_lock;

		} lexer_base, *lexer_base_ptr;
	}
}

#endif // LEXER_BASE_H_
