/*
 * parser.h
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

#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

namespace NIMBLE_NS {
	
	namespace LANGUAGE_NS {
	
		typedef class _parser :
				public lexer {
		
			public:

				_parser(void);

				_parser(
					__in const std::string &input,
					__in_opt bool is_file = true
					);

				_parser(
					__in const _parser &other
					);

				virtual ~_parser(void);

				_parser &operator=(
					__in const _parser &other
					);

				virtual void clear(void);

				virtual void discover(void);

				token_node &get_statement(void);

				token_node &get_statement(
					__in size_t position
					);

				token_node &get_statement(
					__in const uuid &id
					);

				uuid get_statement_id(void);

				uuid get_statement_id(
					__in size_t position
					);

				size_t get_statement_position(void);

				bool has_next_statement(void);

				bool has_previous_statement(void);

				token_node &move_next_statement(void);

				token_node &move_previous_statement(void);

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

				uuid add_child_token(
					__inout token_node &parent_node,
					__in const uuid &parent_id,
					__inout token_node &child_node
					);

				uuid add_control_token(
					__inout token_node &node,
					__in const uuid &parent_id,
					__in token_type type
					);

				uuid add_token(
					__inout token_node &node,
					__in const uuid &parent_id,
					__in const uuid &id
					);

				uuid enumerate_conditional(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_directive(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_expression(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_expression_list(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_function_call(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_function_definition(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_identifier_list(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_identifier_list_parameters(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_identifier_list_result(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_list_operator(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_literal(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_operation(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_statement(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_statement_list(
					__inout token_node &node
					);

				uuid enumerate_statement_list(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_switch_statement(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				uuid enumerate_switch_statement_list(
					__in const uuid &parent_id,
					__inout token_node &node
					);

				std::string node_as_string(
					__in const token_node &node,
					__in_opt bool verbose = false,
					__in_opt size_t tab = 0
					);

				token &token_advance(
					__in_opt bool expect_next = false
					);

				token &token_retreat(
					__in_opt bool expect_previous = false
					);

				std::vector<uuid> m_statement_list;

				size_t m_statement_position;

			private:

				std::recursive_mutex m_parser_lock;

		} parser, *parser_ptr;
	}
}

#endif // PARSER_H_
