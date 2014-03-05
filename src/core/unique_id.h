/*
 * unique_id.h
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

#ifndef UNIQUE_ID_H_
#define UNIQUE_ID_H_

#include "type.h"

namespace NIMBLE_NS {

	#ifndef COMPONENT_NS
	#define COMPONENT_NS component_interface
	#endif // COMPOENT_NS

	namespace COMPONENT_NS {
		
		#ifndef UNIQUE_ID_NS
		#define UNIQUE_ID_NS unique_interface
		#endif // UNIQUE_ID_NS

		namespace UNIQUE_ID_NS {
		
			size_t decrement_reference(
				__in const uuid &id
				);

			void destroy(void);

			uuid generate(
				__in_opt bool unique = false,
				__in_opt size_t *reference_count = NULL
				);

			size_t get_reference_count(
				__in const uuid &id
				);
			
			std::string id_as_string(
				__in const uuid &id
				);

			size_t increment_reference(
				__in const uuid &id
				);

			void initialize(
				__in_opt uint32_t seed = INVALID
				);

			bool is_initialized(void);

			bool is_registered(
				__in const uuid &id
				);

			bool is_unique(
				__in const uuid &id
				);

			size_t register_id(
				__in const uuid &id,
				__in_opt bool unique = false
				);

			size_t registeration_count(void);

			void set_unique(
				__in const uuid &id,
				__in bool unique
				);

			std::string to_string(
				__in_opt bool verbose = false
				);
		}
	}

	bool operator<(
		__in const uuid &left,
		__in const uuid &right
		);

	bool operator==(
		__in const uuid &left,
		__in const uuid &right
		);

	bool operator!=(
		__in const uuid &left,
		__in const uuid &right
		);
}

#endif // UNIQUE_ID_H_
