/*
 * lexer.cpp
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

#include "lexer.h"
#include "lexer_type.h"
#include "token.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_LEXER
	#endif // TRACE_FLAG

	namespace LANGUAGE_NS {

		_lexer::_lexer(void)
		{
			TRACE_ENTRY();

			lexer::clear();

			TRACE_EXIT();
		}

		_lexer::_lexer(
			__in const std::string &input,
			__in_opt bool is_file
			)
		{
			TRACE_ENTRY();

			lexer::set(input, is_file);

			TRACE_EXIT();
		}

		_lexer::_lexer(
			__in const _lexer &other
			) :
				lexer_base(other),
				m_token_list(other.m_token_list),
				m_token_position(other.m_token_position)
		{
			std::vector<uuid>::iterator token_iter;

			TRACE_ENTRY();

			for(token_iter = m_token_list.begin(); token_iter != m_token_list.end(); ++token_iter) {
				COMPONENT_NS::TOKEN_NS::increment_reference(*token_iter);
			}

			TRACE_EXIT();
		}

		_lexer::~_lexer(void)
		{
			TRACE_ENTRY();

			if(COMPONENT_NS::TOKEN_NS::is_initialized()) {
				lexer::clear();
			}

			TRACE_EXIT();
		}

		_lexer &
		_lexer::operator=(
			__in const _lexer &other
			)
		{
			std::vector<uuid>::iterator token_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(this != &other) {

				for(token_iter = m_token_list.begin(); token_iter != m_token_list.end(); ++token_iter) {
					COMPONENT_NS::TOKEN_NS::decrement_reference(*token_iter);
				}

				lexer_base::operator=(other);
				m_token_list = other.m_token_list;
				m_token_position = other.m_token_position;
			
				for(token_iter = m_token_list.begin(); token_iter != m_token_list.end(); ++token_iter) {
					COMPONENT_NS::TOKEN_NS::increment_reference(*token_iter);
				}
			}

			TRACE_EXIT();
			return *this;
		}

		char 
		_lexer::character_advance(
			__in_opt bool expect_next
			)
		{
			char result = CHARACTER_EOS;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(lexer_base::has_next_character()) {
				result = lexer_base::move_next_character();
			} else if(expect_next) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_NEXT_CHARACTER).c_str(), lexer_base::to_string().c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_NEXT_CHARACTER, "%s", lexer_base::to_string().c_str());
			}

			TRACE_EXIT_MESSAGE("%c", result);
			return result;
		}

		char 
		_lexer::character_retreat(
			__in_opt bool expect_previous
			)
		{
			char result = CHARACTER_EOS;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(lexer_base::has_previous_character()) {
				result = lexer_base::move_previous_character();
			} else if(expect_previous) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_PREVIOUS_CHARACTER).c_str(), lexer_base::to_string().c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_PREVIOUS_CHARACTER, "%s", lexer_base::to_string().c_str());
			}

			TRACE_EXIT_MESSAGE("%c", result);
			return result;
		}

		void 
		_lexer::clear(void)
		{
			std::vector<uuid>::iterator token_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			lexer_base::reset();
			
			for(token_iter = m_token_list.begin(); token_iter != m_token_list.end(); ++token_iter) {
				COMPONENT_NS::TOKEN_NS::decrement_reference(*token_iter);
			}

			m_token_list.clear();
			m_token_position = 0;
			m_token_list.push_back(COMPONENT_NS::TOKEN_NS::register_token(TOKEN_TYPE_BEGIN));
			m_token_list.push_back(COMPONENT_NS::TOKEN_NS::register_token(TOKEN_TYPE_END));

			TRACE_EXIT();
		}

		void 
		_lexer::discover(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			lexer::clear();

			while(lexer::has_next_token()) {
				lexer::move_next_token();
			}

			lexer::reset();

			TRACE_EXIT();
		}

		void 
		_lexer::enumerate_alpha_token(
			__inout token &tok
			)
		{
			char current_char;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			current_char = lexer_base::get_character();
			tok.type = TOKEN_TYPE_IDENTIFIER;

			if((lexer_base::get_character_type() != CHARACTER_TYPE_ALPHA)
					&& (current_char != CHARACTER_UNDERSCORE)) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_IDENTIFIER).c_str(), lexer_base::to_string().c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_IDENTIFIER, "%s", lexer_base::to_string().c_str());
			}

			while((lexer_base::get_character_type() == CHARACTER_TYPE_ALPHA)
					|| (current_char == CHARACTER_UNDERSCORE)) {
				tok.text += current_char;

				if(!lexer_base::has_next_character()) {
					break;
				}

				current_char = character_advance();
			}

			TRANSFORM(::tolower, tok.text);

			if(IS_CONDITIONAL_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_CONDITIONAL;
			} else if(IS_CONSTANT_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_CONSTANT;
			} else if(IS_DIRECTIVE_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_DIRECTIVE;
			} else if(IS_FUNCTION_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_FUNCTION;
			} else if(IS_FUNCTION_DEFINITION_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_FUNCTION_DEFINITION;
			} else if(IS_LIST_OPERATOR_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_LIST_OPERATOR;
			} else if(IS_OPERATOR_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_OPERATOR;
			} else if(IS_SWITCH_STATEMENT_END_TYPE(tok.text)) {
				tok.type = TOKEN_TYPE_SWITCH_STATEMENT_END;
			}

			if(tok.type != TOKEN_TYPE_IDENTIFIER) {
				tok.subtype = determine_subtype(tok.text, tok.type);
				tok.text.clear();
			}

			TRACE_EXIT();
		}

		void 
		_lexer::enumerate_digit_token(
			__inout token &tok
			)
		{
			char current_char;
			std::string exception_string;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			current_char = lexer_base::get_character();
			exception_string = lexer_base::to_string();
			tok.type = TOKEN_TYPE_VALUE_LITERAL;
			tok.subtype = VALUE_TYPE_POSITIVE;

			if((lexer_base::get_character_type() != CHARACTER_TYPE_DIGIT)
					&& (current_char != CHARACTER_NEGATION)) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_VALUE).c_str(), exception_string.c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_VALUE, "%s", exception_string.c_str());
			}

			if(current_char == CHARACTER_NEGATION) {
				tok.subtype = VALUE_TYPE_NEGATIVE;

				if(!lexer_base::has_next_character()) {
					TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_VALUE).c_str(), exception_string.c_str());
					THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_VALUE, "%s", exception_string.c_str());
				}

				current_char = character_advance();
			}

			if(lexer_base::get_character_type() != CHARACTER_TYPE_DIGIT) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_VALUE).c_str(), exception_string.c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_VALUE, "%s", exception_string.c_str());
			}

			while(lexer_base::get_character_type() == CHARACTER_TYPE_DIGIT) {
				tok.text += current_char;

				if(!lexer_base::has_next_character()) {
					break;
				}

				current_char = character_advance();
			}

			if(current_char == CHARACTER_DECIMAL) {
				tok.text += current_char;

				if(!lexer_base::has_next_character()) {
					TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_VALUE).c_str(), exception_string.c_str());
					THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_VALUE, "%s", exception_string.c_str());
				}

				current_char = character_advance();

				if(lexer_base::get_character_type() != CHARACTER_TYPE_DIGIT) {
					TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_VALUE).c_str(), exception_string.c_str());
					THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_VALUE, "%s", exception_string.c_str());
				}

				while(lexer_base::get_character_type() == CHARACTER_TYPE_DIGIT) {
					tok.text += current_char;

					if(!lexer_base::has_next_character()) {
						break;
					}

					current_char = character_advance();
				}
			}

			UNREFERENCED_PARAMETER(tok);

			TRACE_EXIT();
		}

		void 
		_lexer::enumerate_string_token(
			__inout token &tok
			)
		{
			char current_char;
			std::string exception_string;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			current_char = lexer_base::get_character();
			exception_string = lexer_base::to_string();
			tok.type = TOKEN_TYPE_STRING_LITERAL;

			if(current_char != CHARACTER_STRING_DELIMITER) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_STRING).c_str(), exception_string.c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_STRING, "%s", exception_string.c_str());
			}

			if(!lexer_base::has_next_character()) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_STRING).c_str(), exception_string.c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_STRING, "%s", exception_string.c_str());
			}

			current_char = character_advance();

			while(current_char != CHARACTER_STRING_DELIMITER) {
				tok.text += current_char;

				if(!lexer_base::has_next_character()) {
					TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_UNTERMINATED_STRING).c_str(), exception_string.c_str());
					THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_UNTERMINATED_STRING, "%s", exception_string.c_str());
				}

				current_char = character_advance();
			}

			character_advance();

			TRACE_EXIT();
		}

		void 
		_lexer::enumerate_symbol_token(
			__inout token &tok
			)
		{
			char current_char;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			current_char = lexer_base::get_character();

			if(lexer_base::get_character_type() != CHARACTER_TYPE_SYMBOL) {
				TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_SYMBOL).c_str(), lexer_base::to_string().c_str());
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_SYMBOL, "%s", lexer_base::to_string().c_str());
			}

			switch(current_char) {
				case CHARACTER_NEGATION:
					enumerate_digit_token(tok);
					break;
				case CHARACTER_STRING_DELIMITER:
					enumerate_string_token(tok);
					break;
				case CHARACTER_UNDERSCORE:
					enumerate_alpha_token(tok);
					break;
				default:
					tok.text += current_char;
					
					if(IS_OPERATOR_TYPE(tok.text)) {
						tok.type = TOKEN_TYPE_OPERATOR;
					} else if(IS_SYMBOL_TYPE(tok.text)) {
						tok.type = TOKEN_TYPE_SYMBOL;
					} else {
						TRACE_ERROR("%s: %s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_SYMBOL).c_str(), lexer_base::to_string().c_str());
						THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_EXPECTING_SYMBOL, "%s", lexer_base::to_string().c_str());
					}

					tok.subtype = determine_subtype(tok.text, tok.type);
					tok.text.clear();
					character_advance();
					break;
			}

			TRACE_EXIT();
		}

		void 
		_lexer::enumerate_token(
			__inout token &tok
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			INITIALIZE_TOKEN(tok);

			tok.line = lexer_base::get_character_row();
			
			if(lexer_base::has_source_path()) {
				tok.source = lexer_base::get_source_path();
			}

			switch(lexer_base::get_character_type()) {
				case CHARACTER_TYPE_ALPHA:
					enumerate_alpha_token(tok);
					break;
				case CHARACTER_TYPE_DIGIT:
					enumerate_digit_token(tok);
					break;
				case CHARACTER_TYPE_SYMBOL:
					enumerate_symbol_token(tok);
					break;
				default:
					TRACE_ERROR("%s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_EXPECTING_TOKEN).c_str());
					THROW_LEXER_EXCEPTION(LEXER_EXCEPTION_EXPECTING_TOKEN);
			}

			TRACE_EXIT();
		}

		uuid 
		_lexer::get_begin_token_id(void)
		{
			uuid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			result = m_token_list.front();

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result));
			return result;
		}

		uuid 
		_lexer::get_end_token_id(void)
		{
			uuid result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			result = m_token_list.back();

			TRACE_EXIT_MESSAGE("%s", COMPONENT_NS::UNIQUE_ID_NS::id_as_string(result));
			return result;
		}

		token &
		_lexer::get_token(void)
		{
			return get_token(m_token_position);
		}

		token &
		_lexer::get_token(
			__in size_t position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(position >= m_token_list.size()) {
				TRACE_ERROR("%s: %lu", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_INVALID_TOKEN_POSITION).c_str(), position);
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_INVALID_TOKEN_POSITION, "%lu", position);
			}

			TRACE_EXIT();
			return COMPONENT_NS::TOKEN_NS::get_token(m_token_list.at(position));
		}

		token &
		_lexer::get_token(
			__in const uuid &id
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);
			TRACE_EXIT();
			return COMPONENT_NS::TOKEN_NS::get_token(id);
		}

		uuid 
		_lexer::get_token_id(void)
		{
			return get_token_id(m_token_position);
		}

		uuid 
		_lexer::get_token_id(
			__in size_t position
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(position >= m_token_list.size()) {
				TRACE_ERROR("%s: %lu", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_INVALID_TOKEN_POSITION).c_str(), position);
				THROW_LEXER_EXCEPTION_MESSAGE(LEXER_EXCEPTION_INVALID_TOKEN_POSITION, "%lu", position);
			}

			TRACE_EXIT();
			return m_token_list.at(position);
		}

		size_t 
		_lexer::get_token_position(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);
			TRACE_EXIT_MESSAGE("%lu", m_token_position);
			return m_token_position;
		}

		bool 
		_lexer::has_next_token(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			result = (lexer::get_token().type != TOKEN_TYPE_END);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		bool 
		_lexer::has_previous_token(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			result = (m_token_position > 0);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		token &
		_lexer::move_next_token(void)
		{
			token tok;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(!lexer::has_next_token()) {
				TRACE_ERROR("%s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_NO_NEXT_TOKEN).c_str());
				THROW_LEXER_EXCEPTION(LEXER_EXCEPTION_NO_NEXT_TOKEN);
			}

			skip_whitespace();

			if(lexer_base::has_next_character() && (m_token_position <= (m_token_list.size() - 2))) {
				enumerate_token(tok);
				m_token_list.insert(m_token_list.begin() + m_token_position + 1, COMPONENT_NS::TOKEN_NS::register_token(tok));
			}

			++m_token_position;

			TRACE_EXIT();
			return lexer::get_token();
		}

		token &
		_lexer::move_previous_token(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			if(!lexer::has_previous_token()) {
				TRACE_ERROR("%s", LEXER_EXCEPTION_STRING(LEXER_EXCEPTION_NO_PREVIOUS_TOKEN).c_str());
				THROW_LEXER_EXCEPTION(LEXER_EXCEPTION_NO_PREVIOUS_TOKEN);
			}

			--m_token_position;

			TRACE_EXIT();
			return lexer::get_token();
		}

		void 
		_lexer::reset(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			m_token_position = 0;

			TRACE_EXIT();
		}

		void 
		_lexer::set(
			__in const std::string &input,
			__in_opt bool is_file
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			lexer::clear();
			lexer_base::set(input, is_file);

			TRACE_EXIT();
		}

		size_t 
		_lexer::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			result = m_token_list.size();

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		void 
		_lexer::skip_whitespace(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			while(lexer_base::has_next_character()) {
				
				if(lexer_base::get_character_type() != CHARACTER_TYPE_WHITESPACE) {
					break;
				}

				lexer_base::move_next_character();
			}

			if(lexer_base::get_character() == CHARACTER_COMMENT) {
				
				while(lexer_base::has_next_character()) {
					
					if(lexer_base::get_character() == CHARACTER_NEWLINE) {
						break;
					}

					lexer_base::move_next_character();
				}

				if(lexer_base::has_next_character()) {
					lexer_base::move_next_character();
				}
			}

			if((lexer_base::get_character() == CHARACTER_COMMENT) 
					|| (lexer_base::get_character_type() == CHARACTER_TYPE_WHITESPACE)) {
				skip_whitespace();
			}

			TRACE_EXIT();
		}

		std::string 
		_lexer::to_string(
			__in_opt bool verbose
			)
		{
			token current_token;
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_lock);

			current_token = lexer::get_token();

			if(verbose) {
				stream << "{" << m_token_position << "} ";
			}

			stream << COMPONENT_NS::TOKEN_NS::token_as_string(current_token, verbose);

			TRACE_EXIT();
			return stream.str();
		}
	}
}
