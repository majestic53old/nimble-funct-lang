/*
 * type.h
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

#ifndef TYPE_H_
#define TYPE_H_

#include <algorithm>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#ifndef NIMBLE_NS
#define NIMBLE_NS nimble
#endif // NIMBLE_NS

namespace NIMBLE_NS {
	
	#define FUNCT_NAME __FUNCTION__
	#define FUNCT_NAME_VERBOSE __FUNCTION__ " @ " TO_STRING(__LINE__)
	#define FUNCT_ENTRY "+" __FUNCTION__
	#define FUNCT_EXIT "-" __FUNCTION__
	#define INITIAL_REFERENCE_COUNT (1)
	#define INVALID (-1)
	#define MAX_MESSAGE_LENGTH (0x400)
	#define SENTINEL_COUNT (2)
	#define UNKNOWN "UNKNOWN"
	#define _SERIALIZE_CALL(_TYPE_, _MUTEX_) std::lock_guard<_TYPE_> __LOCK(_MUTEX_)
	#define SERIALIZE_CALL(_MUTEX_) _SERIALIZE_CALL(std::mutex, _MUTEX_)
	#define SERIALIZE_CALL_RECURSIVE(_MUTEX_) _SERIALIZE_CALL(std::recursive_mutex, _MUTEX_)
	#define _TO_STRING_X(_TXT_) #_TXT_
	#define TO_STRING(_TXT_) _TO_STRING_X(_TXT_)
	#define TRANSFORM(_FUNCTION_, _VECTOR_)\
		std::transform((_VECTOR_).begin(), (_VECTOR_).end(), (_VECTOR_).begin(), _FUNCTION_)
	#define _VALUE_AS_HEX(_TYPE_, _FILL_, _VALUE_)\
		std::setw(sizeof(_TYPE_) * 2) << std::setfill(_FILL_) << std::hex << (size_t) ((_TYPE_) (_VALUE_)) << std::dec
	#define VALUE_AS_HEX(_TYPE_, _VALUE_) _VALUE_AS_HEX(_TYPE_, '0', _VALUE_)

	#define CHARACTER_COMMENT ';'
	#define CHARACTER_DECIMAL '.'
	#define CHARACTER_EOS '\0'
	#define CHARACTER_NEGATION '~'
	#define CHARACTER_NEWLINE '\n'
	#define CHARACTER_STRING_DELIMITER '\"'
	#define CHARACTER_TAB '\t'
	#define CHARACTER_UNDERSCORE '_'

	typedef enum {
		CHARACTER_TYPE_ALPHA = 0,
		CHARACTER_TYPE_DIGIT,
		CHARACTER_TYPE_SYMBOL,
		CHARACTER_TYPE_WHITESPACE,
	} character_type;

	static const std::string CHARACTER_TYPE_STR[] = {
		"ALPHA", "DIGIT", "SYMBOL", "WHITESPACE",
		};

	#define MAX_CHARACTER_TYPE CHARACTER_TYPE_WHITESPACE
	#define CHARACTER_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_CHARACTER_TYPE ? UNKNOWN : CHARACTER_TYPE_STR[_TYPE_])

	typedef enum {
		CONDITIONAL_IF = 0,
		CONDITIONAL_SWITCH,
		CONDITIONAL_WHILE,
	} conditional_type;

	static const std::string CONDITIONAL_TYPE_STR[] = {
		"if", "switch", "while",
		};

	#define MAX_CONDITIONAL_TYPE CONDITIONAL_WHILE
	#define CONDITIONAL_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_CONDITIONAL_TYPE ? UNKNOWN : CONDITIONAL_TYPE_STR[_TYPE_])

	static const std::set<std::string> CONDITIONAL_TYPE_SET = {
		CONDITIONAL_TYPE_STR,
		CONDITIONAL_TYPE_STR + (MAX_CONDITIONAL_TYPE + 1)
		};

	#define IS_CONDITIONAL_TYPE(_STRING_)\
		(CONDITIONAL_TYPE_SET.find(_STRING_) != CONDITIONAL_TYPE_SET.end())

	typedef enum {
		CONSTANT_FALSE = 0,
		CONSTANT_TRUE,
	} constant_type;

	static const std::string CONSTANT_TYPE_STR[] = {
		"false", "true",
		};

	#define MAX_CONSTANT_TYPE CONSTANT_TRUE
	#define CONSTANT_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_CONSTANT_TYPE ? UNKNOWN : CONSTANT_TYPE_STR[_TYPE_])

	static const std::set<std::string> CONSTANT_TYPE_SET = {
		CONSTANT_TYPE_STR,
		CONSTANT_TYPE_STR + (MAX_CONSTANT_TYPE + 1)
		};

	#define IS_CONSTANT_TYPE(_STRING_)\
		(CONSTANT_TYPE_SET.find(_STRING_) != CONSTANT_TYPE_SET.end())

	typedef enum {
		DIRECTIVE_BREAK = 0,
		DIRECTIVE_CONTINUE,
		DIRECTIVE_RETURN,
	} directive_type;

	static const std::string DIRECTIVE_TYPE_STR[] = {
		"break", "continue", "return",
		};

	#define MAX_DIRECTIVE_TYPE DIRECTIVE_RETURN
	#define DIRECTIVE_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_DIRECTIVE_TYPE ? UNKNOWN : DIRECTIVE_TYPE_STR[_TYPE_])

	static const std::set<std::string> DIRECTIVE_TYPE_SET = {
		DIRECTIVE_TYPE_STR,
		DIRECTIVE_TYPE_STR + (MAX_DIRECTIVE_TYPE + 1)
		};

	#define IS_DIRECTIVE_TYPE(_STRING_)\
		(DIRECTIVE_TYPE_SET.find(_STRING_) != DIRECTIVE_TYPE_SET.end())

	typedef enum {
		FUNCTION_CALL = 0,
		FUNCTION_POSTDEC,
		FUNCTION_POSTINC,
		FUNCTION_PREDEC,
		FUNCTION_PREINC,
		FUNCTION_PRINT,
		FUNCTION_SET,
		FUNCTION_UNDEF,
	} function_type;

	static const std::string FUNCTION_TYPE_STR[] = {
		"call", "postdec", "postinc", "predec", "preinc", "print", "set", "undef",
		};

	#define MAX_FUNCTION_TYPE FUNCTION_UNDEF
	#define FUNCTION_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_FUNCTION_TYPE ? UNKNOWN : FUNCTION_TYPE_STR[_TYPE_])

	static const std::set<std::string> FUNCTION_TYPE_SET = {
		FUNCTION_TYPE_STR,
		FUNCTION_TYPE_STR + (MAX_FUNCTION_TYPE + 1)
		};

	#define IS_FUNCTION_TYPE(_STRING_)\
		(FUNCTION_TYPE_SET.find(_STRING_) != FUNCTION_TYPE_SET.end())

	typedef enum {
		FUNCTION_DEFINITION_DEF = 0
	} function_definition_type;

	static const std::string FUNCTION_DEFINITION_TYPE_STR[] = {
		"def",
		};

	#define MAX_FUNCTION_DEFINITION_TYPE FUNCTION_DEFINITION_DEF
	#define FUNCTION_DEFINITION_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_FUNCTION_DEFINITION_TYPE ? UNKNOWN : FUNCTION_DEFINITION_TYPE_STR[_TYPE_])

	static const std::set<std::string> FUNCTION_DEFINITION_TYPE_SET = {
		FUNCTION_DEFINITION_TYPE_STR,
		FUNCTION_DEFINITION_TYPE_STR + (MAX_FUNCTION_DEFINITION_TYPE + 1)
		};

	#define IS_FUNCTION_DEFINITION_TYPE(_STRING_)\
		(FUNCTION_DEFINITION_TYPE_SET.find(_STRING_) != FUNCTION_DEFINITION_TYPE_SET.end())

	typedef struct {
		bool initialized;
		std::recursive_mutex lock;
	} interface_state, *interface_state_ptr;

	typedef enum {
		LIST_OPERATOR_BEGIN = 0,
		LIST_OPERATOR_END,
		LIST_OPERATOR_POP,
		LIST_OPERATOR_PUSH,
	} list_operator_type;

	static const std::string LIST_OPERATOR_TYPE_STR[] = {
		"begin", "end", "pop", "push",
		};

	#define MAX_LIST_OPERATOR_TYPE LIST_OPERATOR_PUSH
	#define LIST_OPERATOR_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_LIST_OPERATOR_TYPE ? UNKNOWN : LIST_OPERATOR_TYPE_STR[_TYPE_])

	static const std::set<std::string> LIST_OPERATOR_TYPE_SET = {
		LIST_OPERATOR_TYPE_STR,
		LIST_OPERATOR_TYPE_STR + (MAX_LIST_OPERATOR_TYPE + 1)
		};

	#define IS_LIST_OPERATOR_TYPE(_STRING_)\
		(LIST_OPERATOR_TYPE_SET.find(_STRING_) != LIST_OPERATOR_TYPE_SET.end())

	typedef enum {
		OPERATOR_ADDITION = 0,
		OPERATOR_AND,
		OPERATOR_DIVISION,
		OPERATOR_EQUALS,
		OPERATOR_GREATER_THAN,
		OPERATOR_LESS_THAN,
		OPERATOR_MODULUS,
		OPERATOR_MULTIPLICATION,
		OPERATOR_NOT_EQUALS,
		OPERATOR_OR,
		OPERATOR_SUBTRACTION,
		OPERATOR_XOR,
	} operator_type;

	static const std::string OPERATOR_TYPE_STR[] = {
		"+", "&", "/", "=", ">", "<", "%", "*",
		"!", "|", "-", "^",
		};

	#define MAX_OPERATOR_TYPE OPERATOR_XOR
	#define OPERATOR_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_OPERATOR_TYPE ? UNKNOWN : OPERATOR_TYPE_STR[_TYPE_])

	static const std::set<std::string> OPERATOR_TYPE_SET = {
		OPERATOR_TYPE_STR,
		OPERATOR_TYPE_STR + (MAX_OPERATOR_TYPE + 1)
		};

	#define IS_OPERATOR_TYPE(_STRING_)\
		(OPERATOR_TYPE_SET.find(_STRING_) != OPERATOR_TYPE_SET.end())

	typedef enum {
		SWITCH_STATEMENT_END_ELSE = 0,
	} switch_statement_end_type;

	static const std::string SWITCH_STATEMENT_END_STR[] = {
		"else",
		};

	#define MAX_SWITCH_STATEMENT_END_TYPE SWITCH_STATEMENT_END_ELSE
	#define SWITCH_STATEMENT_END_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_SWITCH_STATEMENT_END_TYPE ? UNKNOWN : SWITCH_STATEMENT_END_STR[_TYPE_])

	static const std::set<std::string> SWITCH_STATEMENT_END_SET = {
		SWITCH_STATEMENT_END_STR,
		SWITCH_STATEMENT_END_STR + (MAX_SWITCH_STATEMENT_END_TYPE + 1)
		};

	#define IS_SWITCH_STATEMENT_END_TYPE(_STRING_)\
		(SWITCH_STATEMENT_END_SET.find(_STRING_) != SWITCH_STATEMENT_END_SET.end())

	typedef enum {
		SYMBOL_CLOSE_PARENTHESIS = 0,
		SYMBOL_OPEN_PARENTHESIS,
	} symbol_type;

	static const std::string SYMBOL_TYPE_STR[] = {
		")", "(",
		};

	#define MAX_SYMBOL_TYPE SYMBOL_OPEN_PARENTHESIS
	#define SYMBOL_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_SYMBOL_TYPE ? UNKNOWN : SYMBOL_TYPE_STR[_TYPE_])

	static const std::set<std::string> SYMBOL_TYPE_SET = {
		SYMBOL_TYPE_STR,
		SYMBOL_TYPE_STR + (MAX_SYMBOL_TYPE + 1)
		};

	#define IS_SYMBOL_TYPE(_STRING_)\
		(SYMBOL_TYPE_SET.find(_STRING_) != SYMBOL_TYPE_SET.end())

	typedef enum {
		VALUE_TYPE_NEGATIVE = 0,
		VALUE_TYPE_POSITIVE,
	} value_type;

	static const std::string VALUE_TYPE_STR[] = {
		"-", "+",
		};

	#define MAX_VALUE_TYPE VALUE_TYPE_POSITIVE
	#define VALUE_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_VALUE_TYPE ? UNKNOWN : VALUE_TYPE_STR[_TYPE_])

	static const size_t SUBTYPE_LEN[] = {
		0, MAX_CONDITIONAL_TYPE + 1, MAX_CONSTANT_TYPE + 1, MAX_DIRECTIVE_TYPE + 1, 0, 0, 0, MAX_FUNCTION_TYPE + 1, 
		0, MAX_FUNCTION_DEFINITION_TYPE + 1, 0, 0, 0, 0, MAX_LIST_OPERATOR_TYPE + 1, 0, MAX_OPERATOR_TYPE + 1, 0, 0, 
		0, MAX_SYMBOL_TYPE + 1, 0, MAX_SWITCH_STATEMENT_END_TYPE + 1, 0, MAX_VALUE_TYPE + 1,
		};

	static const std::string *SUBTYPE_STR[] = {
		NULL, CONDITIONAL_TYPE_STR, CONSTANT_TYPE_STR, DIRECTIVE_TYPE_STR, NULL, NULL, NULL, FUNCTION_TYPE_STR, 
		NULL, FUNCTION_DEFINITION_TYPE_STR, NULL, NULL, NULL, NULL, LIST_OPERATOR_TYPE_STR, NULL, OPERATOR_TYPE_STR, 
		NULL, NULL, NULL, SYMBOL_TYPE_STR, NULL, SWITCH_STATEMENT_END_STR, NULL, VALUE_TYPE_STR,
		};

	typedef enum {
		TOKEN_TYPE_BEGIN = 0,
		TOKEN_TYPE_CONDITIONAL,
		TOKEN_TYPE_CONSTANT,
		TOKEN_TYPE_DIRECTIVE,
		TOKEN_TYPE_END,
		TOKEN_TYPE_EXPRESSION,
		TOKEN_TYPE_EXPRESSION_LIST,
		TOKEN_TYPE_FUNCTION,
		TOKEN_TYPE_FUNCTION_CALL,
		TOKEN_TYPE_FUNCTION_DEFINITION,
		TOKEN_TYPE_IDENTIFIER,
		TOKEN_TYPE_IDENTIFIER_LIST,
		TOKEN_TYPE_IDENTIFIER_LIST_PARAMETERS,
		TOKEN_TYPE_IDENTIFIER_LIST_RESULT,
		TOKEN_TYPE_LIST_OPERATOR,
		TOKEN_TYPE_OPERATION,
		TOKEN_TYPE_OPERATOR,
		TOKEN_TYPE_STATEMENT,
		TOKEN_TYPE_STATEMENT_LIST,
		TOKEN_TYPE_STRING_LITERAL,
		TOKEN_TYPE_SYMBOL,
		TOKEN_TYPE_SWITCH_STATEMENT,
		TOKEN_TYPE_SWITCH_STATEMENT_END,
		TOKEN_TYPE_SWITCH_STATEMENT_LIST,
		TOKEN_TYPE_VALUE_LITERAL,
	} token_type;

	static const token_type CONTROL_TOKEN_TYPE[] = {
		TOKEN_TYPE_BEGIN, TOKEN_TYPE_END, TOKEN_TYPE_EXPRESSION, TOKEN_TYPE_EXPRESSION_LIST, TOKEN_TYPE_FUNCTION_CALL, 
		TOKEN_TYPE_FUNCTION_DEFINITION, TOKEN_TYPE_IDENTIFIER_LIST, TOKEN_TYPE_IDENTIFIER_LIST_PARAMETERS, TOKEN_TYPE_IDENTIFIER_LIST_RESULT, 
		TOKEN_TYPE_OPERATION, TOKEN_TYPE_STATEMENT, TOKEN_TYPE_STATEMENT_LIST, TOKEN_TYPE_SWITCH_STATEMENT, TOKEN_TYPE_SWITCH_STATEMENT_LIST,
		};

	#define CONTROL_TOKEN_COUNT (sizeof(CONTROL_TOKEN_TYPE) / sizeof(token_type))

	static const std::set<token_type> CONTROL_TOKEN_SET = {
		CONTROL_TOKEN_TYPE,
		CONTROL_TOKEN_TYPE + CONTROL_TOKEN_COUNT
		};

	#define IS_CONTROL_TOKEN(_TYPE_)\
		(CONTROL_TOKEN_SET.find((token_type) (_TYPE_)) != CONTROL_TOKEN_SET.end())

	static const token_type LITERAL_TOKEN_TYPE[] = {
		TOKEN_TYPE_CONSTANT, TOKEN_TYPE_IDENTIFIER, TOKEN_TYPE_STRING_LITERAL, TOKEN_TYPE_VALUE_LITERAL,
		};

	#define LITERAL_TOKEN_COUNT (sizeof(LITERAL_TOKEN_TYPE) / sizeof(token_type))

	static const std::set<token_type> LITERAL_TOKEN_SET = {
		LITERAL_TOKEN_TYPE,
		LITERAL_TOKEN_TYPE + LITERAL_TOKEN_COUNT
		};

	#define IS_LITERAL_TOKEN(_TYPE_)\
		(LITERAL_TOKEN_SET.find((token_type) (_TYPE_)) != LITERAL_TOKEN_SET.end())

	static const std::string TOKEN_TYPE_STR[] = {
		"BEGIN", "CONDITIONAL", "CONSTANT", "DIRECTIVE", "END", "EXPRESSION", "EXPRESSION_LIST",
		"FUNCTION", "FUNCTION_CALL", "FUNCTION_DEFINITION", "IDENTIFIER", "IDENTIFIER_LIST", 
		"IDENTIFIER_LIST_PARAMETERS", "IDENTIFIER_LIST_RESULT", "LIST_OPERATOR", "OPERATION", 
		"OPERATOR", "STATEMENT", "STATEMENT_LIST", "STRING_LITERAL", "SYMBOL", "SWITCH_STATEMENT", 
		"SWITCH_STATEMENT_END", "SWITCH_STATEMENT_LIST", "VALUE_LITERAL",
		};

	typedef uint16_t token_subtype;

	#define INVALID_SUBTYPE ((token_subtype) INVALID)
	#define INVALID_TYPE ((token_type) INVALID)
	#define MAX_TOKEN_TYPE TOKEN_TYPE_VALUE_LITERAL
	#define SUBTYPE_LENGTH(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_TOKEN_TYPE ? 0 : SUBTYPE_LEN[_TYPE_])
	#define SUBTYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_TOKEN_TYPE ? NULL : SUBTYPE_STR[_TYPE_])
	#define TOKEN_TYPE_STRING(_TYPE_)\
		(((size_t) _TYPE_) > (size_t) MAX_TOKEN_TYPE ? UNKNOWN : TOKEN_TYPE_STR[_TYPE_])

	typedef struct {
		size_t line;
		std::string source;
		token_subtype subtype;
		std::string text;
		token_type type;
	} token, *token_ptr;

	#define INITIALIZE_TOKEN(_TOKEN_) {\
		(_TOKEN_).line = 0;\
		(_TOKEN_).source.clear();\
		(_TOKEN_).subtype = INVALID_SUBTYPE;\
		(_TOKEN_).type = INVALID_TYPE;\
		(_TOKEN_).text.clear();\
		}

	#define IS_TOKEN_TYPE(_TOKEN_, _TYPE_)\
		(((token) _TOKEN_).type == ((token_type) (_TYPE_)))

	#define IS_TOKEN_SUBTYPE(_TOKEN_, _TYPE_, _SUBTYPE_)\
		((((token) _TOKEN_).type == ((token_type) (_TYPE_))) && (((token) _TOKEN_).subtype == ((token_subtype) (_SUBTYPE_))))

	typedef enum {
		UUID_BLOCK_HIGH = 0,
		UUID_BLOCK_LOW,
	} uuid_block;

	#define UUID_BLOCK_COUNT (2)

	typedef struct {
		uint64_t block[UUID_BLOCK_COUNT];
	} uuid, *uuid_ptr;

	#define INITIALIZE_UUID(_UUID_) memset(&(_UUID_), 0, sizeof(uuid))
	#define IS_VALID_UUID(_UUID_) ((_UUID_).block[UUID_BLOCK_HIGH] || (_UUID_).block[UUID_BLOCK_LOW])
	static uuid NULL_UUID = {0};

	typedef struct {
		uuid id;
		uuid parent;
		std::vector<uuid> children;
	} token_node, *token_node_ptr;

	#define INITIALIZE_TOKEN_NODE(_NODE_) {\
		INITIALIZE_UUID((_NODE_).id);\
		INITIALIZE_UUID((_NODE_).parent);\
		(_NODE_).children.clear();\
		}

	inline token_subtype 
	determine_subtype(
		__in const std::string &input,
		__in token_type type
		)
	{
		const std::string *type_string = NULL;
		token_subtype result = INVALID_SUBTYPE;
		size_t type_string_length = SUBTYPE_LENGTH(type);

		if(type_string_length > 0) {
			type_string = SUBTYPE_STRING(type);

			if(type_string != NULL) {
			
				for(result = 0; result < type_string_length; ++result) {
					
					if(type_string[result] == input) {
						break;
					}
				}

				if(result >= type_string_length) {
					result = INVALID_SUBTYPE;
				}
			}
		}

		return result;
	}

	inline std::string 
	determine_subtype_string(
		__in token_type type,
		__in token_subtype subtype
		)
	{
		std::string result = UNKNOWN;

		if(type <= MAX_TOKEN_TYPE) {
		
			if(subtype < SUBTYPE_LENGTH(type)) {
				result = SUBTYPE_STRING(type)[subtype];
			}
		}

		return result;
	}

	inline std::string 
	format_as_string(
		__in_opt const char *format = NULL,
		...
		)
	{
		int length = 0;
		va_list arguments = NULL;
		std::stringstream stream;
		char message_buffer[MAX_MESSAGE_LENGTH];

		if(format) {
			memset(message_buffer, 0, sizeof(char) * MAX_MESSAGE_LENGTH);
			va_start(arguments, format);
#ifdef _WIN32
			length = vsnprintf_s(message_buffer, _countof(message_buffer), _TRUNCATE, format, arguments);
#else
			length = snprintf(message_buffer, sizeof(char) * MAX_MESSAGE_LENGTH, format, arguments);
#endif // _WIN32

			if(length > 0) {
				stream << ": " << message_buffer;
			}
			va_end(arguments);
		}

		return stream.str();
	}

	template <typename Type, typename Funct> Type
	transform(
		__in const Type &input,
		__in const Funct &function
		)
	{
		Type output = input;

		TRANSFORM(function, output);

		return output;
	}
}

#endif // TYPE_H_
