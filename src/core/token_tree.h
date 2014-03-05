/*
 * token_tree.h
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

#ifndef TOKEN_TREE_H_
#define TOKEN_TREE_H_

#include "type.h"

namespace NIMBLE_NS {

	#ifndef COMPONENT_NS
	#define COMPONENT_NS component_interface
	#endif // COMPOENT_NS

	namespace COMPONENT_NS {
	
		#ifndef TOKEN_TREE_NS
		#define TOKEN_TREE_NS token_tree_interface
		#endif // TOKEN_TREE_NS

		namespace TOKEN_TREE_NS {

			size_t decrement_reference(
				__in const uuid &id
				);

			void destroy(void);

			token_node &get_node(
				__in const uuid &id
				);

			size_t get_reference_count(
				__in const uuid &id
				);

			size_t increment_reference(
				__in const uuid &id
				);

			void initialize(void);

			bool is_initialized(void);

			bool is_registered(
				__in const uuid &id
				);

			std::string node_as_string(
				__in const token_node &node,
				__in_opt bool verbose = false
				);

			uuid register_node(
				__in const uuid &id
				);

			uuid register_node(
				__in const uuid &id,
				__in const uuid &parent
				);

			uuid register_node(
				__in const uuid &id,
				__in const uuid &parent,
				__in const std::vector<uuid> &children
				);

			uuid register_node(
				__in const token_node &node
				);

			size_t registeration_count(void);

			std::string to_string(
				__in_opt bool verbose = false
				);
		}
	}

	bool operator==(
		__in const token_node &left,
		__in const token_node &right
		);

	bool operator!=(
		__in const token_node &left,
		__in const token_node &right
		);
}

#endif // TOKEN_TREE_H_
