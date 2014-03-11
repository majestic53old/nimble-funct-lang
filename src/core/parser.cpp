/*
 * parser.cpp
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

#include "parser.h"
#include "parser_type.h"
#include "token.h"
#include "token_tree.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_PARSER
	#endif // TRACE_FLAG

	namespace LANGUAGE_NS {

		_parser::_parser(void)
		{
			TRACE_ENTRY();

			parser::clear();

			TRACE_EXIT();
		}

		_parser::_parser(
			__in const std::string &input,
			__in_opt bool is_file
			)
		{
			TRACE_ENTRY();

			parser::set(input, is_file);

			TRACE_EXIT();
		}

		_parser::_parser(
			__in const _parser &other
			) :
				lexer(other),
				m_statement_list(other.m_statement_list),
				m_statement_position(other.m_statement_position)
		{
			std::vector<uuid>::const_iterator node_iter;

			TRACE_ENTRY();

			for(node_iter = m_statement_list.begin(); node_iter != m_statement_list.end(); ++node_iter) {
				COMPONENT_NS::TOKEN_TREE_NS::increment_reference(*node_iter);
			}

			TRACE_EXIT();
		}

		_parser::~_parser(void)
		{
			TRACE_ENTRY();

			if(COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
				parser::clear();
			}

			TRACE_EXIT();
		}

		_parser &
		_parser::operator=(
			__in const _parser &other
			)
		{
			std::vector<uuid>::const_iterator node_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(this != &other) {

				for(node_iter = m_statement_list.begin(); node_iter != m_statement_list.end(); ++node_iter) {
					COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(*node_iter);
				}

				lexer::operator=(other);
				m_statement_list = other.m_statement_list;
				m_statement_position = other.m_statement_position;

				for(node_iter = m_statement_list.begin(); node_iter != m_statement_list.end(); ++node_iter) {
					COMPONENT_NS::TOKEN_TREE_NS::increment_reference(*node_iter);
				}
			}

			TRACE_EXIT();
			return *this;
		}

		uuid 
		_parser::add_child_token(
			__inout token_node &parent_node,
			__in const uuid &parent_id,
			__inout token_node &child_node
			)
		{
			uuid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			child_node.parent = parent_id;
			result = COMPONENT_NS::TOKEN_TREE_NS::register_node(child_node);
			parent_node.children.push_back(result);

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::add_control_token(
			__inout token_node &node,
			__in const uuid &parent_id,
			__in token_type type
			)
		{
			uuid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = COMPONENT_NS::TOKEN_TREE_NS::register_node(COMPONENT_NS::TOKEN_NS::register_token(type), parent_id);
			node = COMPONENT_NS::TOKEN_TREE_NS::get_node(result);

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::add_token(
			__inout token_node &node,
			__in const uuid &parent_id,
			__in const uuid &id
			)
		{
			uuid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = COMPONENT_NS::TOKEN_TREE_NS::register_node(id, parent_id);
			node = COMPONENT_NS::TOKEN_TREE_NS::get_node(result);

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		void 
		_parser::clear(void)
		{
			std::vector<uuid>::const_iterator node_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			lexer::reset();

			for(node_iter = m_statement_list.begin(); node_iter != m_statement_list.end(); ++node_iter) {
				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(*node_iter);
			}

			m_statement_list.clear();
			m_statement_position = 0;
			m_statement_list.push_back(COMPONENT_NS::TOKEN_TREE_NS::register_node(lexer::get_begin_token_id()));
			m_statement_list.push_back(COMPONENT_NS::TOKEN_TREE_NS::register_node(lexer::get_end_token_id()));

			TRACE_EXIT();
		}

		void 
		_parser::discover(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			parser::clear();

			while(parser::has_next_statement()) {
				parser::move_next_statement();
			}

			parser::reset();

			TRACE_EXIT();
		}

		uuid 
		_parser::enumerate_conditional(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node expression_node, statement_node, statement_node_alt;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			INITIALIZE_TOKEN_NODE(expression_node);
			INITIALIZE_TOKEN_NODE(statement_node);
			INITIALIZE_TOKEN_NODE(statement_node_alt);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_CONDITIONAL)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CONDITIONAL).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CONDITIONAL, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			switch(current_tok.subtype) {
				case CONDITIONAL_IF:
					result = add_token(node, parent_id, lexer::get_token_id());
					token_advance(true);
					enumerate_expression(result, expression_node);
					enumerate_statement(result, statement_node);
					current_tok = lexer::get_token();
					
					if(IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
						token_advance(true);
						enumerate_statement(result, statement_node_alt);
						current_tok = lexer::get_token();

						if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
							TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
								COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
							THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
								COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
						}

						token_advance();
					}
					break;
				case CONDITIONAL_SWITCH:
					result = add_token(node, parent_id, lexer::get_token_id());
					token_advance(true);
					enumerate_expression(result, expression_node);
					enumerate_switch_statement_list(result, statement_node);
					break;
				case CONDITIONAL_WHILE:
					result = add_token(node, parent_id, lexer::get_token_id());
					token_advance(true);
					enumerate_expression(result, expression_node);
					enumerate_statement(result, statement_node);
					break;
				default:
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_UNKNOWN_CONDITIONAL).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_UNKNOWN_CONDITIONAL, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_directive(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_DIRECTIVE)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_DIRECTIVE).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_DIRECTIVE, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			switch(current_tok.subtype) {
				case DIRECTIVE_BREAK:
				case DIRECTIVE_CONTINUE:
				case DIRECTIVE_RETURN:
					result = add_token(node, parent_id, lexer::get_token_id());
					token_advance();
					break;
				default:
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_UNKNOWN_DIRECTIVE).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_UNKNOWN_DIRECTIVE, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_expression(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			INITIALIZE_TOKEN_NODE(child_node);
			result = add_control_token(node, parent_id, TOKEN_TYPE_EXPRESSION);
			current_tok = lexer::get_token();

			if(IS_LITERAL_TOKEN(current_tok.type)) {
				enumerate_literal(result, child_node);
			} else {

				if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				}

				current_tok = token_advance(true);

				switch(current_tok.type) {
					case TOKEN_TYPE_FUNCTION:
						enumerate_function_call(result, child_node);
						break;
					case TOKEN_TYPE_LIST_OPERATOR:
						enumerate_list_operator(result, child_node);
						break;
					case TOKEN_TYPE_OPERATOR:
						enumerate_operation(result, child_node);
						break;
					default:
						enumerate_expression(result, child_node);
						break;
				}

				current_tok = lexer::get_token();

				if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				}

				token_advance();
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_expression_list(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_EXPRESSION_LIST);
			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_expression(result, child_node);
			current_tok = lexer::get_token();

			while(IS_LITERAL_TOKEN(current_tok.type) || IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				INITIALIZE_TOKEN_NODE(child_node);
				enumerate_expression(result, child_node);
				current_tok = lexer::get_token();

				if(!lexer::has_next_token()) {
					break;
				}
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_function_call(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			token_node child_node;
			uuid function_result, result;
			token current_tok, function_tok;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_FUNCTION_CALL);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_FUNCTION)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_FUNCTION_CALL).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_FUNCTION_CALL, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			function_tok = lexer::get_token();
			function_result = add_token(child_node, result, lexer::get_token_id());
			current_tok = token_advance(true);

			switch(function_tok.subtype) {
				case FUNCTION_CALL:

					if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
						TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(),
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
						THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", 
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					}

					INITIALIZE_TOKEN_NODE(child_node);
					add_token(child_node, result, lexer::get_token_id());
					current_tok = token_advance();

					if(IS_LITERAL_TOKEN(current_tok.type) || IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
						INITIALIZE_TOKEN_NODE(child_node);
						enumerate_expression_list(result, child_node);
					}
					break;
				case FUNCTION_POSTDEC:
				case FUNCTION_POSTINC:
				case FUNCTION_PREDEC:
				case FUNCTION_PREINC:
				case FUNCTION_UNDEF:

					if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
						TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(),
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
						THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", 
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					}

					INITIALIZE_TOKEN_NODE(child_node);
					add_token(child_node, result, lexer::get_token_id());
					token_advance();
					break;
				case FUNCTION_PRINT:
					INITIALIZE_TOKEN_NODE(child_node);
					enumerate_expression(result, child_node);
					break;
				case FUNCTION_SET:

					if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
						TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(),
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
						THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", 
							COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					}

					INITIALIZE_TOKEN_NODE(child_node);
					add_token(child_node, result, lexer::get_token_id());
					token_advance(true);
					INITIALIZE_TOKEN_NODE(child_node);
					enumerate_expression(result, child_node);
					break;
				default:
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_UNKNOWN_FUNCTION_CALL).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(function_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_UNKNOWN_FUNCTION_CALL, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(function_tok).c_str());
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_function_definition(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_FUNCTION_DEFINITION)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_FUNCTION_DEFINITION).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_FUNCTION_DEFINITION, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			result = add_token(node, parent_id, lexer::get_token_id());
			current_tok = token_advance(true);

			if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			current_tok = token_advance(true);

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			add_token(child_node, result, lexer::get_token_id());
			current_tok = token_advance(true);

			if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			current_tok = token_advance(true);

			if(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				INITIALIZE_TOKEN_NODE(child_node);
				enumerate_identifier_list(result, child_node);
			}

			current_tok = lexer::get_token();

			if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_OPENING_PARENTHESIS, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			current_tok = token_advance(true);
			enumerate_statement(result, child_node);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			token_advance();

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_identifier_list(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_IDENTIFIER_LIST);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_identifier_list_parameters(result, child_node);
			current_tok = lexer::get_token();

			if(IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				INITIALIZE_TOKEN_NODE(child_node);
				current_tok = token_advance(true);
				enumerate_identifier_list_result(result, child_node);
				current_tok = lexer::get_token();

				if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				}

				token_advance();
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_identifier_list_parameters(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_IDENTIFIER_LIST_PARAMETERS);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_PARAMETERS).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_PARAMETERS, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			add_token(child_node, result, lexer::get_token_id());
			current_tok = token_advance();

			while(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				add_token(child_node, result, lexer::get_token_id());
				current_tok = token_advance();

				if(!lexer::has_next_token()) {
					break;
				}
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_identifier_list_result(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_IDENTIFIER_LIST_RESULT);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_RESULT).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER_LIST_RESULT, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			add_token(child_node, result, lexer::get_token_id());
			current_tok = token_advance();

			if(IS_LITERAL_TOKEN(current_tok.type) || IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				INITIALIZE_TOKEN_NODE(child_node);
				enumerate_expression(result, child_node);
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_list_operator(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token_node child_node;
			token current_tok, list_operator_tok;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_LIST_OPERATOR)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_LIST_OPERATOR).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_LIST_OPERATOR, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			result = add_token(node, parent_id, lexer::get_token_id());
			list_operator_tok = lexer::get_token();
			current_tok = token_advance(true);

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			add_token(child_node, result, lexer::get_token_id());

			switch(list_operator_tok.subtype) {
				case LIST_OPERATOR_BEGIN:
				case LIST_OPERATOR_END:
				case LIST_OPERATOR_POP:
					token_advance();
					break;
				case LIST_OPERATOR_PUSH:
					INITIALIZE_TOKEN_NODE(child_node);
					current_tok = token_advance(true);
					enumerate_expression(result, child_node);
					break;
				default:
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_UNKNOWN_LIST_OPERATOR).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(list_operator_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_UNKNOWN_LIST_OPERATOR, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(list_operator_tok).c_str());
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_literal(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_CONSTANT) 
				&& !IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_IDENTIFIER)
				&& !IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_STRING_LITERAL) 
				&& !IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_VALUE_LITERAL))
			{
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_LITERAL_VALUE).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_LITERAL_VALUE, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			result = add_token(node, parent_id, lexer::get_token_id());
			token_advance();

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_operation(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_OPERATION);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_OPERATOR)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_OPERATOR).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_OPERATOR, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			INITIALIZE_TOKEN_NODE(child_node);
			add_token(child_node, result, lexer::get_token_id());
			token_advance(true);
			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_expression_list(result, child_node);

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_statement(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			INITIALIZE_TOKEN_NODE(child_node);
			result = add_control_token(node, parent_id, TOKEN_TYPE_STATEMENT);
			current_tok = lexer::get_token();

			switch(current_tok.type) {
				case TOKEN_TYPE_CONDITIONAL:
					enumerate_conditional(result, child_node);
					break;
				case TOKEN_TYPE_DIRECTIVE:
					enumerate_directive(result, child_node);
					break;
				default:
					enumerate_expression(result, child_node);
					break;
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_statement_list(
			__inout token_node &node
			)
		{
			return enumerate_statement_list(NULL_UUID, node);
		}

		uuid 
		_parser::enumerate_statement_list(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token current_tok;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_STATEMENT_LIST);
			current_tok = lexer::get_token();

			if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_STATEMENT_LIST).c_str(),
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_STATEMENT_LIST, "%s", 
					COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
			}

			while(IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				INITIALIZE_TOKEN_NODE(child_node);
				current_tok = token_advance(true);

				if(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_FUNCTION)) {
					enumerate_function_call(result, child_node);
				} else if(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_FUNCTION_DEFINITION)) {
					enumerate_function_definition(result, child_node);
				} else if(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_LIST_OPERATOR)) {
					enumerate_list_operator(result, child_node);
				} else if(IS_TOKEN_TYPE(current_tok, TOKEN_TYPE_OPERATOR)) {
					enumerate_operation(result, child_node);
				} else {
					enumerate_statement(result, child_node);
				}

				current_tok = lexer::get_token();

				if(!IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_CLOSE_PARENTHESIS)) {
					TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS).c_str(),
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
					THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_CLOSING_PARENTHESIS, "%s", 
						COMPONENT_NS::TOKEN_NS::token_as_string(current_tok).c_str());
				}

				current_tok = token_advance();

				if(!lexer::has_next_token()) {
					break;
				}
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_switch_statement(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			uuid result;
			token_node child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_SWITCH_STATEMENT);
			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_literal(result, child_node);
			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_statement(result, child_node);

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		uuid 
		_parser::enumerate_switch_statement_list(
			__in const uuid &parent_id,
			__inout token_node &node
			)
		{
			token current_tok;
			uuid else_result, result;
			token_node child_node, else_child_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = add_control_token(node, parent_id, TOKEN_TYPE_SWITCH_STATEMENT_LIST);
			INITIALIZE_TOKEN_NODE(child_node);
			enumerate_switch_statement(result, child_node);
			current_tok = lexer::get_token();

			while(IS_LITERAL_TOKEN(current_tok.type) || IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SYMBOL, SYMBOL_OPEN_PARENTHESIS)) {
				INITIALIZE_TOKEN_NODE(child_node);
				enumerate_switch_statement(result, child_node);
				current_tok = lexer::get_token();
			}

			if(IS_TOKEN_SUBTYPE(current_tok, TOKEN_TYPE_SWITCH_STATEMENT_END, SWITCH_STATEMENT_END_ELSE)) {
				INITIALIZE_TOKEN_NODE(child_node);
				else_result = add_token(child_node, result, lexer::get_token_id());
				token_advance(true);
				INITIALIZE_TOKEN_NODE(else_child_node);
				enumerate_statement(else_result, else_child_node);
			}

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result).c_str());
			return result;
		}

		token_node &
		_parser::get_statement(void)
		{
			return get_statement(m_statement_position);
		}

		token_node &
		_parser::get_statement(
			__in size_t position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(position >= m_statement_list.size()) {
				TRACE_ERROR("%s: %lu", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_INVALID_STATEMENT_POSITION).c_str(), position);
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_INVALID_STATEMENT_POSITION, "%lu", position);
			}

			TRACE_EXIT();
			return COMPONENT_NS::TOKEN_TREE_NS::get_node(m_statement_list.at(position));
		}

		token_node &
		_parser::get_statement(
			__in const uuid &id
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);
			TRACE_EXIT();
			return COMPONENT_NS::TOKEN_TREE_NS::get_node(id);	
		}

		uuid 
		_parser::get_statement_id(void)
		{
			return get_statement_id(m_statement_position);
		}

		uuid 
		_parser::get_statement_id(
			__in size_t position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(position >= m_statement_list.size()) {
				TRACE_ERROR("%s: %lu", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_INVALID_STATEMENT_POSITION).c_str(), position);
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_INVALID_STATEMENT_POSITION, "%lu", position);
			}

			TRACE_EXIT();
			return m_statement_list.at(position);
		}

		size_t 
		_parser::get_statement_position(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);
			TRACE_EXIT_MESSAGE("%lu", m_statement_position);
			return m_statement_position;
		}

		bool 
		_parser::has_next_statement(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = (get_statement().id != lexer::get_end_token_id());

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		bool 
		_parser::has_previous_statement(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = (m_statement_position > 0);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		token_node &
		_parser::move_next_statement(void)
		{
			token_node root_node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(!parser::has_next_statement()) {
				TRACE_ERROR("%s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_NO_NEXT_STATEMENT).c_str());
				THROW_PARSER_EXCEPTION(PARSER_EXCEPTION_NO_NEXT_STATEMENT);
			}

			INITIALIZE_TOKEN_NODE(root_node);

			if(lexer::get_token().type == TOKEN_TYPE_BEGIN) {
				token_advance();
			}

			if(lexer::has_next_token() && (m_statement_position <= (m_statement_list.size() - SENTINEL_COUNT))) {
				m_statement_list.insert(m_statement_list.begin() + m_statement_position + 1, 
					enumerate_statement_list(root_node));
			}
			
			++m_statement_position;

			TRACE_EXIT();
			return parser::get_statement();
		}

		token_node &
		_parser::move_previous_statement(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(!parser::has_previous_statement()) {
				TRACE_ERROR("%s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT).c_str());
				THROW_PARSER_EXCEPTION(PARSER_EXCEPTION_NO_PREVIOUS_STATEMENT);
			}

			--m_statement_position;

			TRACE_EXIT();
			return parser::get_statement();
		}

		std::string 
		_parser::node_as_string(
			__in const token_node &node,
			__in_opt bool verbose,
			__in_opt size_t tab
			)
		{
			size_t tab_iter;
			std::stringstream stream;
			std::vector<uuid>::const_iterator node_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			for(tab_iter = 0; tab_iter < tab; ++tab_iter) {
				stream << "------";
			}

			if(tab) {
				stream << " ";
			}

			stream << COMPONENT_NS::TOKEN_NS::token_as_string(lexer::get_token(node.id), verbose);

			if(verbose && !node.children.empty()) {
				stream << "[" << node.children.size() << "]";
			}

			for(node_iter = node.children.begin(); node_iter != node.children.end(); ++node_iter) {
				stream << std::endl << node_as_string(parser::get_statement(*node_iter), verbose, tab + 1);
			}

			TRACE_EXIT();
			return stream.str();
		}

		void 
		_parser::reset(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			m_statement_position = 0;

			TRACE_EXIT();
		}

		void 
		_parser::set(
			__in const std::string &input,
			__in_opt bool is_file
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			lexer::set(input, is_file);
			parser::clear();

			TRACE_EXIT();
		}

		size_t 
		_parser::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			result = m_statement_list.size() - SENTINEL_COUNT;

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		std::string 
		_parser::to_string(
			__in_opt bool verbose 
			)
		{
			token_node current_node;
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			current_node = parser::get_statement();

			if(verbose) {
				stream << "{" << m_statement_position << "} ";
			}

			stream << parser::node_as_string(current_node, verbose);

			TRACE_EXIT();
			return stream.str();
		}

		token &
		_parser::token_advance(
			__in_opt bool expect_next
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(!lexer::has_next_token() && expect_next) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_NEXT_TOKEN).c_str(), lexer::to_string().c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_NEXT_TOKEN, "%s", lexer::to_string().c_str());
			}

			TRACE_EXIT();
			return lexer::move_next_token();
		}

		token &
		_parser::token_retreat(
			__in_opt bool expect_previous
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_parser_lock);

			if(!lexer::has_previous_token() && expect_previous) {
				TRACE_ERROR("%s: %s", PARSER_EXCEPTION_STRING(PARSER_EXCEPTION_EXPECTING_PREVIOUS_TOKEN).c_str(), lexer::to_string().c_str());
				THROW_PARSER_EXCEPTION_MESSAGE(PARSER_EXCEPTION_EXPECTING_PREVIOUS_TOKEN, "%s", lexer::to_string().c_str());
			}

			TRACE_EXIT();
			return lexer::move_previous_token();
		}
	}
}
