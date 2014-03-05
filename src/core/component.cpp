/*
 * component.cpp
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

#include "component.h"
#include "component_type.h"
#include "token.h"
#include "token_tree.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_COMPONENT
	#endif // TRACE_FLAG

	namespace COMPONENT_NS {

		typedef struct {
			interface_state state;
		} component_interface_state, *component_interface_state_ptr;

		static component_interface_state g_component_state;

		void 
		destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(g_component_state.state.lock);

			if(!g_component_state.state.initialized) {
				TRACE_ERROR("%s", COMPONENT_EXCEPTION_STRING(COMPONENT_EXCEPTION_UNINITIALIZED).c_str());
				THROW_COMPONENT_EXCEPTION(COMPONENT_EXCEPTION_UNINITIALIZED);
			}

			if(TOKEN_TREE_NS::is_initialized()) {
				TOKEN_TREE_NS::destroy();
			}

			if(TOKEN_NS::is_initialized()) {
				TOKEN_NS::destroy();
			}

			if(UNIQUE_ID_NS::is_initialized()) {
				UNIQUE_ID_NS::destroy();
			}

			g_component_state.state.initialized = false;

			TRACE_EXIT();
		}

		void 
		initialize(
			__in_opt uint32_t seed
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(g_component_state.state.lock);
			
			if(g_component_state.state.initialized) {
				destroy();
			}

			UNIQUE_ID_NS::initialize(seed);
			TOKEN_NS::initialize();
			TOKEN_TREE_NS::initialize();
			g_component_state.state.initialized = true;

			TRACE_EXIT();
		}

		bool 
		is_initialized(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(g_component_state.state.lock);

			result = g_component_state.state.initialized;

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		std::string 
		to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(g_component_state.state.lock);

			stream << "[" << COMPONENT_HEADER << "] " 
				<< (g_component_state.state.initialized ? "Initialized" : "Uninitialized")
				<< std::endl << "--- " << UNIQUE_ID_NS::to_string(verbose)
				<< std::endl << "--- " << TOKEN_NS::to_string(verbose)
				<< std::endl << "--- " << TOKEN_TREE_NS::to_string(verbose);

			TRACE_EXIT();
			return stream.str();
		}
	}
}
