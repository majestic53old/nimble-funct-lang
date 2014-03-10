/*
 * version.h
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

#ifndef VERSION_H_
#define VERSION_H_

#include "type.h"

namespace NIMBLE_NS {

	#define LIBRARY_TITLE "Nimble Language Library"
	#define LIBRARY_COPYRIGHT "Copyright (C) 2014 David Jolly"

	#define LIBARY_VERSION_MAJOR 0
	#define LIBARY_VERSION_MINOR 1
	#define LIBARY_VERSION_REVISION 1
	#define LIBARY_VERSION_WORKWEEK 1411

	#define LIBRARY_VERSION_RESOURCE\
		TO_STRING(LIBARY_VERSION_MAJOR) "." TO_STRING(LIBARY_VERSION_MINOR) "\0"
	#define LIBRARY_VERSION_RESOURCE_VERBOSE\
		TO_STRING(LIBARY_VERSION_MAJOR) "." TO_STRING(LIBARY_VERSION_MINOR) "."\
			TO_STRING(LIBARY_VERSION_WORKWEEK) TO_STRING(LIBARY_VERSION_REVISION) "\0"
	#define LIBRARY_VERSION_STRING\
		LIBARY_VERSION_MAJOR << "." << LIBARY_VERSION_MINOR << "." << LIBARY_VERSION_WORKWEEK
	#define LIBRARY_VERSION_STRING_VERBOSE\
		LIBARY_VERSION_MAJOR << "." << LIBARY_VERSION_MINOR << "." << LIBARY_VERSION_WORKWEEK\
			<< " (rev. " << LIBARY_VERSION_REVISION << ", " << __DATE__ << ", " << __TIME__ << ")"

	inline std::string 
	library_version(
		__in_opt bool verbose = false,
		__in_opt bool show_title = false,
		__in_opt bool show_copyright = false
		)
	{
		std::stringstream stream;

		if(show_title) {
			stream << LIBRARY_TITLE << " ";
		}

		if(verbose) {
			stream << LIBRARY_VERSION_STRING_VERBOSE;
		} else {
			stream << LIBRARY_VERSION_STRING;
		}

		if(show_copyright) {
			stream << std::endl << LIBRARY_COPYRIGHT;
		}

		return stream.str();
	}
}

#endif VERSION_H_ // VERSION_H_
