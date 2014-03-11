/*
 * lexer.h
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

#ifndef LEXER_H_
#define LEXER_H_

#include "lexer_base.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
	
		typedef class _lexer :
				public lexer_base {
		
			public:
			
				_lexer(void);

				_lexer(
					__in const std::string &input,
					__in_opt bool is_file = true
					);

				_lexer(
					__in const _lexer &other
					);

				virtual ~_lexer(void);

				_lexer &operator=(
					__in const _lexer &other
					);

				virtual void clear(void);

				virtual void discover(void);

				uuid get_begin_token_id(void);

				uuid get_end_token_id(void);

				token &get_token(void);

				token &get_token(
					__in size_t position
					);

				token &get_token(
					__in const uuid &id
					);

				uuid get_token_id(void);

				uuid get_token_id(
					__in size_t position
					);

				size_t get_token_position(void);

				bool has_next_token(void);

				bool has_previous_token(void);

				token &move_next_token(void);

				token &move_previous_token(void);

				virtual void reset(void);

				virtual void set(
					__in const std::string &input,
					__in_opt bool is_file = true
					);

				virtual size_t size(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				char character_advance(
					__in_opt bool expect_next = false
					);

				char character_retreat(
					__in_opt bool expect_previous = false
					);

				void enumerate_alpha_token(
					__inout token &tok,
					__in bool negative = false
					);

				void enumerate_digit_token(
					__inout token &tok,
					__in bool negative = false
					);

				void enumerate_string_token(
					__inout token &tok
					);

				void enumerate_symbol_token(
					__inout token &tok
					);

				void enumerate_token(
					__inout token &tok
					);

				void enumerate_unary_token(
					__inout token &tok
					);

				void skip_whitespace(void);

				std::vector<uuid> m_token_list;

				size_t m_token_position;

			private:

				std::recursive_mutex m_lexer_lock;

		} lexer, *lexer_ptr;
	}
}

#endif // LEXER_H_
