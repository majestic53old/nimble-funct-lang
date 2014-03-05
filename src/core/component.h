/*
 * component.h
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

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "type.h"

namespace NIMBLE_NS {

	#ifndef COMPONENT_NS
	#define COMPONENT_NS component_interface
	#endif // COMPOENT_NS

	namespace COMPONENT_NS {
	
		void destroy(void);

		void initialize(
			__in_opt uint32_t seed = INVALID
			);

		bool is_initialized(void);

		std::string to_string(
			__in_opt bool verbose = false
			);
	}
}

#endif // COMPONENT_H_
