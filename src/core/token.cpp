/*
 * token.cpp
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

#include <map>
#include "token.h"
#include "token_type.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_TOKEN
	#endif // TRACE_FLAG

	namespace COMPONENT_NS {

		namespace TOKEN_NS {

			typedef struct {
				uuid id;
				size_t reference_count;
				token tok;
			} token_context, *token_context_ptr;

			#define INITIALIZE_TOKEN_CONTEXT(_CONTEXT_, _ID_) {\
				(_CONTEXT_).id = _ID_;\
				(_CONTEXT_).reference_count = INITIAL_REFERENCE_COUNT;\
				INITIALIZE_TOKEN((_CONTEXT_).tok);\
				}

			typedef struct {
				interface_state state;
				std::map<uuid, token_context> token_map;
			} token_interface_state, *token_interface_state_ptr;

			static token_interface_state g_token_state;

			std::map<uuid, token_context>::iterator 
			find_token_context(
				__in const uuid &id
				)
			{
				std::map<uuid, token_context>::iterator token_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				token_iter = g_token_state.token_map.find(id);
				if(token_iter == g_token_state.token_map.end()) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_REGISTERED).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_REGISTERED, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				TRACE_EXIT();
				return token_iter;
			}

			size_t 
			decrement_reference(
				__in const uuid &id
				)
			{
				size_t result = 0;
				std::map<uuid, token_context>::iterator context;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				context = find_token_context(id);
				if(context->second.reference_count == INITIAL_REFERENCE_COUNT) {
					UNIQUE_ID_NS::decrement_reference(id);
					g_token_state.token_map.erase(id);
				} else {
					result = (--context->second.reference_count);
				}

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			void 
			destroy(void)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				g_token_state.token_map.clear();
				g_token_state.state.initialized = false;

				TRACE_EXIT();
			}

			size_t 
			get_reference_count(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = find_token_context(id)->second.reference_count;

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			token &
			get_token(
				__in const uuid &id
				)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				TRACE_EXIT();
				return find_token_context(id)->second.tok;
			}

			size_t 
			increment_reference(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = (++find_token_context(id)->second.reference_count);

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			void 
			initialize(void)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(g_token_state.state.initialized) {
					destroy();
				}

				g_token_state.token_map.clear();
				g_token_state.state.initialized = true;

				TRACE_EXIT();
			}

			bool 
			is_initialized(void)
			{
				bool result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				result = g_token_state.state.initialized;

				TRACE_EXIT_MESSAGE("%i", result);
				return result;
			}

			bool 
			is_registered(
				__in const uuid &id
				)
			{
				bool result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_EXCEPTION_MESSAGE(TOKEN_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = (g_token_state.token_map.find(id) != g_token_state.token_map.end());

				TRACE_EXIT_MESSAGE("%i", result);
				return result;
			}

			uuid 
			register_token(
				__in token_type type,
				__in_opt token_subtype subtype,
				__in_opt const std::string source,
				__in_opt size_t line
				)
			{
				return register_token(std::string(), type, subtype, source, line);
			}

			uuid 
			register_token(
				__in const std::string &text,
				__in token_type type,
				__in_opt token_subtype subtype,
				__in_opt const std::string source,
				__in_opt size_t line
				)
			{
				uuid result;
				token_context context;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				INITIALIZE_TOKEN_CONTEXT(context, UNIQUE_ID_NS::generate());
				context.tok.line = line;
				context.tok.source = source;
				context.tok.subtype = subtype;
				context.tok.text = text;
				context.tok.type = type;
				g_token_state.token_map.insert(std::pair<uuid, token_context>(context.id, context));
				result = context.id;

				TRACE_EXIT_MESSAGE("%s", UNIQUE_ID_NS::id_as_string(result).c_str());
				return result;
			}

			uuid 
			register_token(
				__in const token &tok
				)
			{
				return register_token(tok.text, tok.type, tok.subtype, tok.source, tok.line);
			}

			size_t 
			registeration_count(void)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				if(!g_token_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_EXCEPTION_STRING(TOKEN_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_EXCEPTION(TOKEN_EXCEPTION_UNINITIALIZED);
				}

				result = g_token_state.token_map.size();

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			std::string 
			to_string(
				__in_opt bool verbose
				)
			{
				std::stringstream stream;
				std::map<uuid, token_context>::iterator token_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				stream << "[" << TOKEN_HEADER << "] " 
					<< (g_token_state.state.initialized ? "Initialized" : "Uninitialized");

				if(verbose && g_token_state.state.initialized) {
					stream << ", Count: " << g_token_state.token_map.size();

					for(token_iter = g_token_state.token_map.begin(); token_iter != g_token_state.token_map.end(); ++token_iter) {
						stream << std::endl << "--- " << UNIQUE_ID_NS::id_as_string(token_iter->second.id) << " (ref. " 
							<< token_iter->second.reference_count << ") " << token_as_string(token_iter->second.tok, verbose);
					}
				}

				TRACE_EXIT();
				return stream.str();
			}

			std::string 
			token_as_string(
				__in const token &tok,
				__in_opt bool verbose
				)
			{
				std::stringstream stream;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_state.state.lock);

				stream << "[" << TOKEN_TYPE_STRING(tok.type);

				if(tok.subtype != INVALID_SUBTYPE) {
					stream << ", \'" << determine_subtype_string(tok.type, tok.subtype) 
						<< "\'";

					if(verbose) {
						stream << " (" << VALUE_AS_HEX(token_subtype, tok.subtype) << ")";
					}
				}

				stream << "]";

				if(!tok.text.empty()) {
					stream << " \"" << tok.text << "\"";
				}

				if(!IS_CONTROL_TOKEN(tok.type)) {
					stream << " (";

					if(!tok.source.empty()) {
						stream << tok.source;
					}

					stream << " @ " << tok.line << ")";
				}

				TRACE_EXIT();
				return stream.str();
			}
		}
	}

	bool 
	operator==(
		__in const token &left,
		__in const token &right
		)
	{
		return ((left.line == right.line)
			&& (left.source == right.source)
			&& (left.subtype == right.subtype)
			&& (left.text == right.text)
			&& (left.type == right.type));
	}

	bool 
	operator!=(
		__in const token &left,
		__in const token &right
		)
	{
		return !(left == right);
	}
}
