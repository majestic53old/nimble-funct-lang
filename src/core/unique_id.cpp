/*
 * unique_id.cpp
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

#include <ctime>
#include <map>
#include <random>
#include "trace.h"
#include "unique_id.h"
#include "unique_id_type.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_UNIQUE_ID
	#endif // TRACE_FLAG

	namespace COMPONENT_NS {

		namespace UNIQUE_ID_NS {

			typedef struct {
				uuid id;
				size_t reference_count;
				bool unique;
			} unique_id_context, *unique_id_context_ptr;

			#define INITIALIZE_UNIQUE_ID_CONTEXT(_CONTEXT_, _ID_, _UNIQUE_) {\
				(_CONTEXT_).id = _ID_;\
				(_CONTEXT_).reference_count = INITIAL_REFERENCE_COUNT;\
				(_CONTEXT_).unique = _UNIQUE_;\
				}

			typedef struct {
				std::uniform_int_distribution<uint64_t> distribution;
				std::mt19937_64 generator;
				std::map<uuid, unique_id_context> uuid_map;
				uint32_t seed;
				interface_state state;
			} unique_interface_state, *unique_interface_state_ptr;

			static unique_interface_state g_unique_state;

			std::map<uuid, unique_id_context>::iterator 
			find_id_context(
				__in const uuid &id
				)
			{
				std::map<uuid, unique_id_context>::iterator id_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				id_iter = g_unique_state.uuid_map.find(id);
				if(id_iter == g_unique_state.uuid_map.end()) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_REGISTERED).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_REGISTERED, "%s", id_as_string(id).c_str());
				}

				TRACE_EXIT();
				return id_iter;
			}

			size_t 
			decrement_reference(
				__in const uuid &id
				)
			{
				size_t result = 0;
				std::map<uuid, unique_id_context>::iterator context;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				context = find_id_context(id);
				if(context->second.reference_count == INITIAL_REFERENCE_COUNT) {
					g_unique_state.uuid_map.erase(id);
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
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				g_unique_state.generator.seed(0);
				g_unique_state.uuid_map.clear();
				g_unique_state.seed = 0;
				g_unique_state.state.initialized = false;

				TRACE_EXIT();
			}

			uuid 
			generate(
				__in_opt bool unique,
				__in_opt size_t *reference_count
				)
			{
				uuid result;
				size_t ref_count;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				INITIALIZE_UUID(result);

				do {
					result.block[UUID_BLOCK_HIGH] = g_unique_state.distribution(g_unique_state.generator);
					result.block[UUID_BLOCK_LOW] = g_unique_state.distribution(g_unique_state.generator);

					if(!unique && IS_VALID_UUID(result)) {
						break;
					}
				} while(!is_unique(result) || !IS_VALID_UUID(result));

				ref_count = register_id(result, unique);

				if(reference_count) {
					(*reference_count) = ref_count;
				}

				TRACE_EXIT_MESSAGE("%s", id_as_string(result).c_str());
				return result;
			}

			size_t 
			get_reference_count(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				result = find_id_context(id)->second.reference_count;

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}
	
			std::string 
			id_as_string(
				__in const uuid &id
				)
			{
				std::stringstream stream;

				TRACE_ENTRY();

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_ID_NOT_VALID);
				}

				stream << "{" << VALUE_AS_HEX(uint32_t, (uint64_t) (id.block[UUID_BLOCK_HIGH] >> 0x20)) << "-"
					<< VALUE_AS_HEX(uint16_t,  (uint64_t) (id.block[UUID_BLOCK_HIGH] >> 0x10)) << "-"
					<< VALUE_AS_HEX(uint16_t, id.block[UUID_BLOCK_HIGH]) << "-"
					<< VALUE_AS_HEX(uint16_t, (uint64_t) (id.block[UUID_BLOCK_LOW] >> 0x30)) << "-"
					<< VALUE_AS_HEX(uint16_t, (uint64_t) (id.block[UUID_BLOCK_LOW] >> 0x20)) << "-"
					<< VALUE_AS_HEX(uint32_t, id.block[UUID_BLOCK_LOW]) << "}";

				TRACE_EXIT();
				return stream.str();
			}

			size_t 
			increment_reference(
				__in const uuid &id
				)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				result = (++find_id_context(id)->second.reference_count);

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			void 
			initialize(
				__in_opt uint32_t seed
				)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(g_unique_state.state.initialized) {
					destroy();
				}

				if(seed == INVALID) {
					std::srand((uint32_t) std::time(NULL));
					seed = std::rand();
				}

				g_unique_state.uuid_map.clear();
				g_unique_state.generator.seed(seed);
				g_unique_state.seed = seed;
				g_unique_state.state.initialized = true;

				TRACE_EXIT();
			}

			bool 
			is_initialized(void)
			{
				bool result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				result = g_unique_state.state.initialized;

				TRACE_EXIT_MESSAGE("%i", result);
				return result;
			}

			bool 
			is_unique(
				__in const uuid &id
				)
			{
				bool result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}
				
				result = (is_registered(id) ? find_id_context(id)->second.unique : true);

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
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				result = (g_unique_state.uuid_map.find(id) != g_unique_state.uuid_map.end());

				TRACE_EXIT_MESSAGE("%i", result);
				return result;
			}

			size_t 
			register_id(
				__in const uuid &id,
				__in_opt bool unique
				)
			{
				size_t result = INITIAL_REFERENCE_COUNT;
				unique_id_context context;
				std::map<uuid, unique_id_context>::iterator id_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				id_iter = g_unique_state.uuid_map.find(id);
				if(id_iter != g_unique_state.uuid_map.end()) {
					
					if(id_iter->second.unique) {
						TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_IS_UNIQUE).c_str(), id_as_string(id).c_str());
						THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_IS_UNIQUE, "%s", id_as_string(id).c_str());
					}
					result = (++id_iter->second.reference_count);
				} else {
					INITIALIZE_UNIQUE_ID_CONTEXT(context, id, unique);
					g_unique_state.uuid_map.insert(std::pair<uuid, unique_id_context>(id, context));
				}

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			size_t 
			registeration_count(void)
			{
				size_t result;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				result = g_unique_state.uuid_map.size();

				TRACE_EXIT_MESSAGE("%lu", result);
				return result;
			}

			void set_unique(
				__in const uuid &id,
				__in bool unique
				)
			{
				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				if(!g_unique_state.state.initialized) {
					TRACE_ERROR("%s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_UNINITIALIZED).c_str());
					THROW_UNIQUE_ID_EXCEPTION(UNIQUE_ID_EXCEPTION_UNINITIALIZED);
				}

				if(!IS_VALID_UUID(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_EXCEPTION_STRING(UNIQUE_ID_EXCEPTION_ID_NOT_VALID).c_str(), id_as_string(id).c_str());
					THROW_UNIQUE_ID_EXCEPTION_MESSAGE(UNIQUE_ID_EXCEPTION_ID_NOT_VALID, "%s", id_as_string(id).c_str());
				}

				g_unique_state.uuid_map.find(id)->second.unique = unique;

				TRACE_EXIT();
			}

			std::string 
			to_string(
				__in_opt bool verbose
				)
			{
				std::stringstream stream;
				std::map<uuid, unique_id_context>::iterator id_iter;

				TRACE_ENTRY();
				SERIALIZE_CALL_RECURSIVE(g_unique_state.state.lock);

				stream << "[" << UNIQUE_ID_HEADER << "] " 
					<< (g_unique_state.state.initialized ? "Initialized" : "Uninitialized");

				if(verbose && g_unique_state.state.initialized) {
					stream << ", Count: " << g_unique_state.uuid_map.size();

					for(id_iter = g_unique_state.uuid_map.begin(); id_iter != g_unique_state.uuid_map.end(); ++id_iter) {
						stream << std::endl << "--- " << id_as_string(id_iter->second.id) << " (ref. " 
							<< id_iter->second.reference_count << ", " << (id_iter->second.unique ? "Unique" : "Non-Unique") 
							<< ")";
					}
				}

				TRACE_EXIT();
				return stream.str();
			}
		}
	}

	bool 
	operator<(
		__in const uuid &left,
		__in const uuid &right
		)
	{
		return ((left.block[UUID_BLOCK_HIGH] < right.block[UUID_BLOCK_HIGH]) 
			|| ((left.block[UUID_BLOCK_HIGH] == right.block[UUID_BLOCK_HIGH]) 
			&& (left.block[UUID_BLOCK_LOW] < right.block[UUID_BLOCK_LOW])));
	}

	bool 
	operator==(
		__in const uuid &left,
		__in const uuid &right
		)
	{
		return ((left.block[UUID_BLOCK_HIGH] == right.block[UUID_BLOCK_HIGH]) 
			&& (left.block[UUID_BLOCK_LOW] == right.block[UUID_BLOCK_LOW]));
	}

	bool 
	operator!=(
		__in const uuid &left,
		__in const uuid &right
		)
	{
		return !(left == right);
	}

}
