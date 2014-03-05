/*
 * lexer_base.cpp
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

#include <fstream>
#include "lexer_base.h"
#include "lexer_base_type.h"
#include "trace.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_LEXER_BASE
	#endif // TRACE_FLAG

	namespace LANGUAGE_NS {

		_lexer_base::_lexer_base(void)
		{
			TRACE_ENTRY();

			lexer_base::clear();

			TRACE_EXIT();
		}

		_lexer_base::_lexer_base(
			__in const std::string &input,
			__in_opt size_t is_file
			)
		{
			TRACE_ENTRY();

			lexer_base::set(input, is_file);

			TRACE_EXIT();
		}

		_lexer_base::_lexer_base(
			__in const _lexer_base &other
			) :
				m_character_column(other.m_character_column),
				m_character_column_length(other.m_character_column_length),
				m_character_position(other.m_character_position),
				m_character_row(other.m_character_row),
				m_character_type(other.m_character_type),
				m_raw_input(other.m_raw_input),
				m_source_path(other.m_source_path)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_lexer_base::~_lexer_base(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_lexer_base &
		_lexer_base::operator=(
			__in const _lexer_base &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			if(this != &other) {
				m_character_column = other.m_character_column;
				m_character_column_length = other.m_character_column_length;
				m_character_position = other.m_character_position;
				m_character_row = other.m_character_row;
				m_character_type = other.m_character_type;
				m_raw_input = other.m_raw_input;
				m_source_path = other.m_source_path;
			}

			TRACE_EXIT();
			return *this;
		}

		void 
		_lexer_base::clear(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			m_character_column = 0;
			m_character_column_length.clear();
			m_character_position = 0;
			m_character_row = 0;
			m_raw_input.clear();
			m_raw_input += CHARACTER_EOS;
			m_source_path.clear();
			m_character_type = lexer_base::determine_character_type(get_character());

			TRACE_EXIT();
		}

		character_type 
		_lexer_base::determine_character_type(
			__in char character
			)
		{
			character_type result = CHARACTER_TYPE_SYMBOL;

			TRACE_ENTRY();

			if(isalpha(character)) {
				result = CHARACTER_TYPE_ALPHA;
			} else if(isdigit(character)) {
				result = CHARACTER_TYPE_DIGIT;
			} else if(isspace(character)) {
				result = CHARACTER_TYPE_WHITESPACE;
			}

			TRACE_EXIT_MESSAGE("%s", CHARACTER_TYPE_STRING(result).c_str());
			return result;
		}

		char 
		_lexer_base::get_character(void)
		{
			return lexer_base::get_character(m_character_position);
		}

		char 
		_lexer_base::get_character(
			__in size_t position
			)
		{
			char result = CHARACTER_EOS;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			if(position >= m_raw_input.size()) {
				TRACE_ERROR("%s: %lu", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_POSITION).c_str(), position);
				THROW_LEXER_BASE_EXCEPTION_MESSAGE(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_POSITION, "%lu", position);
			}

			result = m_raw_input.at(position);

			TRACE_EXIT_MESSAGE("%c", result);
			return result;
		}

		size_t 
		_lexer_base::get_character_column(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT_MESSAGE("%lu", m_character_column);
			return m_character_column;
		}

		size_t 
		_lexer_base::get_character_position(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT_MESSAGE("%lu", m_character_position);
			return m_character_position;
		}

		size_t 
		_lexer_base::get_character_row(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT_MESSAGE("%lu", m_character_row);
			return m_character_row;
		}

		character_type 
		_lexer_base::get_character_type(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT_MESSAGE("%s", CHARACTER_TYPE_STRING(m_character_type).c_str());
			return m_character_type;
		}

		std::string &
		_lexer_base::get_raw_input(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT();
			return m_raw_input;
		}

		std::string 
		_lexer_base::get_source_path(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);
			TRACE_EXIT();
			return m_source_path;
		}

		bool 
		_lexer_base::has_next_character(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			result = (lexer_base::get_character() != CHARACTER_EOS);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		bool 
		_lexer_base::has_previous_character(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			result = (m_character_position > 0);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		bool 
		_lexer_base::has_source_path(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			result = !m_source_path.empty();

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		char 
		_lexer_base::move_next_character(void)
		{
			char result = CHARACTER_EOS;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			if(!lexer_base::has_next_character()) {
				TRACE_ERROR("%s", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_NO_NEXT_CHARACTER).c_str());
				THROW_LEXER_BASE_EXCEPTION(LEXER_BASE_EXCEPTION_NO_NEXT_CHARACTER);
			}

			if(get_character() == CHARACTER_NEWLINE) {

				if(m_character_column_length.find(m_character_row) == m_character_column_length.end()) {
					m_character_column_length.insert(std::pair<size_t, size_t>(m_character_row, m_character_column));
				} else {
					m_character_column_length.at(m_character_row) = m_character_column;
				}

				m_character_column = 0;
				++m_character_row;
			} else {
				++m_character_column;
			}

			result = lexer_base::get_character(++m_character_position);
			m_character_type = lexer_base::determine_character_type(result);
			
			TRACE_EXIT_MESSAGE("%c", result);
			return result;
		}

		char 
		_lexer_base::move_previous_character(void)
		{
			char result = CHARACTER_EOS;
			std::map<size_t, size_t>::iterator column_length_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			if(!lexer_base::has_previous_character()) {
				TRACE_ERROR("%s", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_NO_PREVIOUS_CHARACTER).c_str());
				THROW_LEXER_BASE_EXCEPTION(LEXER_BASE_EXCEPTION_NO_PREVIOUS_CHARACTER);
			}

			result = lexer_base::get_character(--m_character_position);
			if(result == CHARACTER_NEWLINE) {

				column_length_iter = m_character_column_length.find(--m_character_row);
				if(column_length_iter == m_character_column_length.end()) {
					TRACE_ERROR("%s: %lu", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_COLUMN).c_str(), m_character_row);
					THROW_LEXER_BASE_EXCEPTION_MESSAGE(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_COLUMN, "%lu", m_character_row);
				}

				m_character_column = column_length_iter->second;
			} else {

				if(!m_character_column) {
					TRACE_ERROR("%s: %lu", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_COLUMN).c_str(), m_character_row);
					THROW_LEXER_BASE_EXCEPTION_MESSAGE(LEXER_BASE_EXCEPTION_INVALID_CHARACTER_COLUMN, "%lu", m_character_row);
				}

				--m_character_column;
			}

			m_character_type = lexer_base::determine_character_type(result);

			TRACE_EXIT_MESSAGE("%c", result);
			return result;
		}

		void 
		_lexer_base::reset(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			m_character_column = 0;
			m_character_column_length.clear();
			m_character_position = 0;
			m_character_row = 0;
			m_character_type = lexer_base::determine_character_type(get_character());

			TRACE_EXIT();
		}

		void 
		_lexer_base::set(
			__in const std::string &input,
			__in_opt size_t is_file
			)
		{
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			lexer_base::clear();

			if(is_file) {

				std::ifstream file(input.c_str(), std::ios::in);
				if(!file) {
					TRACE_ERROR("%s: %s", LEXER_BASE_EXCEPTION_STRING(LEXER_BASE_EXCEPTION_FILE_NOT_FOUND).c_str(), input.c_str());
					THROW_LEXER_BASE_EXCEPTION_MESSAGE(LEXER_BASE_EXCEPTION_FILE_NOT_FOUND, "%s", input.c_str());
				}

				stream << file.rdbuf();
				m_raw_input = stream.str();
				m_source_path = input;
				file.close();
			} else {
				m_raw_input = input;
			}

			if(m_raw_input.empty() || (m_raw_input.back() != CHARACTER_EOS)) {
				m_raw_input += CHARACTER_EOS;
			}

			m_character_type = determine_character_type(get_character());

			TRACE_EXIT();
		}

		size_t 
		_lexer_base::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			result = m_raw_input.size();

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		std::string 
		_lexer_base::to_string(
			__in_opt bool verbose
			)
		{
			char current_character;
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_lexer_base_lock);

			current_character = lexer_base::get_character();

			if(verbose) {
				stream << "[" << CHARACTER_TYPE_STRING(m_character_type) << "] ";
			}

			if(isprint(current_character)) {
				stream << "\'" << current_character << "\' ";
			}

			stream << "(" << VALUE_AS_HEX(uint8_t, current_character) << ") (pos. " << m_character_position 
				<< ", col. " << m_character_column << ", row. " << m_character_row << ")";

			TRACE_EXIT();
			return stream.str();
		}
	}
}