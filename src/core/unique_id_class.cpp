/*
 * unique_id_class.cpp
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

#include "trace.h"
#include "unique_id_class.h"
#include "unique_id_class_type.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_UNIQUE_ID_CLASS
	#endif // TRACE_FLAG

	namespace COMPONENT_NS {

		_unique_id_class::_unique_id_class(void) :
			m_unique_id(UNIQUE_ID_NS::generate())
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_unique_id_class::_unique_id_class(
			__in const uuid &id,
			__in_opt bool unique
			)
		{
			TRACE_ENTRY();

			set_id(id, unique);

			TRACE_EXIT();
		}

		_unique_id_class::_unique_id_class(
			__in const _unique_id_class &other
			)
		{
			TRACE_ENTRY();

			set_id(other.m_unique_id, UNIQUE_ID_NS::is_unique(other.m_unique_id));

			TRACE_EXIT();
		}

		_unique_id_class::~_unique_id_class(void)
		{
			TRACE_ENTRY();

			if(UNIQUE_ID_NS::is_initialized() && UNIQUE_ID_NS::is_registered(m_unique_id)) {
				UNIQUE_ID_NS::decrement_reference(m_unique_id);
			}

			TRACE_EXIT();
		}

		_unique_id_class &
		_unique_id_class::operator=(
			__in const _unique_id_class &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);

			if(this != &other) {
				set_id(other.m_unique_id, UNIQUE_ID_NS::is_unique(other.m_unique_id));
			}

			TRACE_EXIT();
			return *this;
		}

		uuid 
		_unique_id_class::get_id(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);
			TRACE_EXIT_MESSAGE("%s", UNIQUE_ID_NS::id_as_string(m_unique_id).c_str());
			return m_unique_id;
		}

		size_t 
		_unique_id_class::get_reference_count(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);

			result = UNIQUE_ID_NS::get_reference_count(m_unique_id);

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		bool 
		_unique_id_class::is_unique(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);

			result = UNIQUE_ID_NS::is_unique(m_unique_id);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		void 
		_unique_id_class::set_id(
			__in const uuid &id,
			__in_opt bool unique
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);

			if(IS_VALID_UUID(m_unique_id)
					&& UNIQUE_ID_NS::is_registered(m_unique_id)) {
				UNIQUE_ID_NS::decrement_reference(m_unique_id);
			}

			if(UNIQUE_ID_NS::is_registered(id)) {
				
				if(UNIQUE_ID_NS::is_unique(id)) {
					TRACE_ERROR("%s: %s", UNIQUE_ID_CLASS_EXCEPTION_STRING(UNIQUE_ID_CLASS_EXCEPTION_UNIQUE_ID_ASSIGNMENT).c_str(), 
						UNIQUE_ID_NS::id_as_string(id).c_str());
					THROW_UNIQUE_ID_CLASS_EXCEPTION_MESSAGE(UNIQUE_ID_CLASS_EXCEPTION_UNIQUE_ID_ASSIGNMENT, "%s", 
						UNIQUE_ID_NS::id_as_string(id).c_str());
				}

				UNIQUE_ID_NS::increment_reference(id);

				if(UNIQUE_ID_NS::is_unique(id) != unique) {
					UNIQUE_ID_NS::set_unique(id, unique);
				}
			} else {
				UNIQUE_ID_NS::register_id(id, unique);
			}

			m_unique_id = id;

			TRACE_EXIT();
		}
				
		std::string 
		_unique_id_class::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_unique_id_class_lock);

			stream << UNIQUE_ID_NS::id_as_string(m_unique_id);

			if(verbose) {
				stream << " (ref. " << UNIQUE_ID_NS::get_reference_count(m_unique_id) << ", " 
					<< (UNIQUE_ID_NS::is_unique(m_unique_id) ? "Unique" : "Non-Unique") << ")";
			}

			TRACE_EXIT();
			return stream.str();
		}
	}
}
