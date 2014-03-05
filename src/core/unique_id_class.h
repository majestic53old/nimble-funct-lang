/*
 * unique_id_class.h
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

#ifndef UNIQUE_ID_CLASS_H_
#define UNIQUE_ID_CLASS_H_

#include "unique_id.h"

namespace NIMBLE_NS {

	namespace COMPONENT_NS {
		
		typedef class _unique_id_class {
			
			public:

				_unique_id_class(void);

				_unique_id_class(
					__in const uuid &id,
					__in_opt bool unique = false
					);

				_unique_id_class(
					__in const _unique_id_class &other
					);

				virtual ~_unique_id_class(void);

				_unique_id_class &operator=(
					__in const _unique_id_class &other
					);

				uuid get_id(void);

				size_t get_reference_count(void);

				bool is_unique(void);

				void set_id(
					__in const uuid &id,
					__in_opt bool unique = false
					);
				
				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				uuid m_unique_id;

			private:

				std::recursive_mutex m_unique_id_class_lock;

		} unique_id_class, *unique_id_class_ptr;
	}
}

#endif // UNIQUE_ID_CLASS_H_
