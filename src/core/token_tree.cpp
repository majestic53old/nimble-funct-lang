/*
 * token_tree.cpp
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
#include "token_tree.h"
#include "token_tree_type.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_TOKEN_TREE
	#endif // TRACE_FLAG

	namespace COMPONENT_NS {
	
		namespace TOKEN_TREE_NS {
			
			typedef struct {
				uuid id;
				token_node node;
				size_t reference_count;
			} token_tree_context, *token_tree_context_ptr;

			#define INITIALIZE_TOKEN_TREE_CONTEXT(_CONTEXT_, _ID_) {\
				(_CONTEXT_).id = _ID_;\
				INITIALIZE_TOKEN_NODE((_CONTEXT_).node);\
				(_CONTEXT_).reference_count = INITIAL_REFERENCE_COUNT;\
				}

			typedef struct {
				interface_state state;
				std::map<uuid, token_tree_context> node_map;
			} token_tree_interface_state, *token_tree_interface_state_ptr;

			static token_tree_interface_state g_token_tree_state;

			std::map<uuid, token_tree_context>::iterator 
			find_token_tree_context(
				__in const uuid &id
				)
			{
				std::map<uuid, token_tree_context>::iterator token_tree_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				token_tree_iter = g_token_tree_state.node_map.find(id);
				if(token_tree_iter == g_token_tree_state.node_map.end()) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_REGISTERED).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_REGISTERED, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				TRACE_EXIT();
				return token_tree_iter;
			}

			size_t 
			decrement_reference(
				__in const uuid &id
				)
			{
				size_t result = 0;
				std::map<uuid, token_tree_context>::iterator context;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				context = find_token_tree_context(id);
				if(context->second.reference_count == INITIAL_REFERENCE_COUNT) {
					UNIQUE_ID_NS::decrement_reference(id);
					g_token_tree_state.node_map.erase(id);
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
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				g_token_tree_state.node_map.clear();
				g_token_tree_state.state.initialized = false;

				TRACE_EXIT();
			}

			token_node &
			get_node(
				__in const uuid &id
				)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				TRACE_EXIT();
				return find_token_tree_context(id)->second.node;
			}

			size_t 
			get_reference_count(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = find_token_tree_context(id)->second.reference_count;

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			size_t 
			increment_reference(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = (++find_token_tree_context(id)->second.reference_count);

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			void 
			initialize(void)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(g_token_tree_state.state.initialized) {
					destroy();
				}

				g_token_tree_state.node_map.clear();
				g_token_tree_state.state.initialized = true;

				TRACE_EXIT();
			}

			bool 
			is_initialized(void)
			{
				bool result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				result = g_token_tree_state.state.initialized;

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
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				result = (g_token_tree_state.node_map.find(id) != g_token_tree_state.node_map.end());

				TRACE_EXIT_MESSAGE("%i", result);
				return result;
			}

			std::string 
			node_as_string(
				__in const token_node &node,
				__in_opt bool verbose
				)
			{
				std::stringstream stream;
				std::vector<uuid>::const_iterator node_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				stream << UNIQUE_ID_NS::id_as_string(node.id) << "[" << node.children.size() << "]";

				if(IS_VALID_UUID(node.parent)) {
					stream << ", Parent: " << UNIQUE_ID_NS::id_as_string(node.parent);
				}

				if(verbose) {

					for(node_iter = node.children.begin(); node_iter != node.children.end(); ++node_iter) {
						stream << std::endl << "--- " << UNIQUE_ID_NS::id_as_string(*node_iter);
					}
				}

				TRACE_EXIT();
				return stream.str();
			}

			uuid 
			register_node(
				__in const uuid &id
				)
			{
				return register_node(id, NULL_UUID, std::vector<uuid>());
			}

			uuid 
			register_node(
				__in const uuid &id,
				__in const uuid &parent
				)
			{
				return register_node(id, parent, std::vector<uuid>());
			}

			uuid 
			register_node(
				__in const uuid &id,
				__in const uuid &parent,
				__in const std::vector<uuid> &children
				)
			{
				uuid result;
				token_tree_context context;
				std::vector<uuid>::const_iterator child_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_ID_NOT_VALID).c_str(), UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_TOKEN_TREE_EXCEPTION_MESSAGE(TOKEN_TREE_EXCEPTION_ID_NOT_VALID, "%s", UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				INITIALIZE_TOKEN_TREE_CONTEXT(context, UNIQUE_ID_NS::generate());
				context.node.children = children;
				context.node.id = id;
				context.node.parent = parent;
				g_token_tree_state.node_map.insert(std::pair<uuid, token_tree_context>(context.id, context));
				result = context.id;

				if(IS_VALID_UUID(parent)) {
					find_token_tree_context(parent)->second.node.children.push_back(context.id);
				}

				for(child_iter = children.begin(); child_iter != children.end(); ++child_iter) {
					find_token_tree_context(*child_iter)->second.node.parent = context.id;
				}

				TRACE_EXIT_MESSAGE("%s", UNIQUE_ID_NS::id_as_string(result).c_str());
				return result;
			}

			uuid 
			register_node(
				__in const token_node &node
				)
			{
				return register_node(node.id, node.parent, node.children);
			}

			size_t 
			registeration_count(void)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				if(!g_token_tree_state.state.initialized) {
					TRACE_ERROR("%s", TOKEN_TREE_EXCEPTION_STRING(TOKEN_TREE_EXCEPTION_UNINITIALIZED).c_str());
					THROW_TOKEN_TREE_EXCEPTION(TOKEN_TREE_EXCEPTION_UNINITIALIZED);
				}

				result = g_token_tree_state.node_map.size();

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			std::string 
			to_string(
				__in_opt bool verbose
				)
			{
				std::stringstream stream;
				std::map<uuid, token_tree_context>::iterator token_tree_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_token_tree_state.state.lock);

				stream << "[" << TOKEN_TREE_HEADER << "] " 
					<< (g_token_tree_state.state.initialized ? "Initialized" : "Uninitialized");

				if(verbose && g_token_tree_state.state.initialized) {
					stream << ", Count: " << g_token_tree_state.node_map.size();

					for(token_tree_iter = g_token_tree_state.node_map.begin();
						token_tree_iter != g_token_tree_state.node_map.end();
						++token_tree_iter
						)
					{
						stream << std::endl << "--- " << UNIQUE_ID_NS::id_as_string(token_tree_iter->second.id) << " (ref. " 
							<< token_tree_iter->second.reference_count << ") " << node_as_string(token_tree_iter->second.node, verbose);
					}
				}

				TRACE_EXIT();
				return stream.str();
			}
		}
	}

	bool 
	operator==(
		__in const token_node &left,
		__in const token_node &right
		)
	{
		return ((left.children == right.children)
			&& (left.id == right.id)
			&& (left.parent == right.parent));
	}

	bool 
	operator!=(
		__in const token_node &left,
		__in const token_node &right
		)
	{
		return !(left == right);
	}
}
