/*
 * code_generator.h
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

#ifndef CODE_GENERATOR_H_
#define CODE_GENERATOR_H_

#include "parser.h"

namespace NIMBLE_NS {

	namespace LANGUAGE_NS {
		
		typedef class _code_generator :
				public parser {
		
			public:

				// TODO: ...

			protected:

			private:

				std::recursive_mutex m_code_generator_lock;

		} code_generator, *code_generator_ptr;
	}
}

#endif // CODE_GENERATOR_H_
