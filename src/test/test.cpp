/*
 * test.cpp
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

#include "test.h"
#include "test_type.h"
#include "trace.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_TEST
	#endif // TRACE_FLAG

	namespace TEST_NS {

		_test::_test(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();

			set_name(name);
			test::reset();

			TRACE_EXIT();
		}

		_test::_test(
			__in const _test &other
			) :
				m_name(other.m_name),
				m_result(other.m_result),
				m_run_count(other.m_run_count)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_test::~_test(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_test &
		_test::operator=(
			__in const _test &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);

			if(this != &other) {
				m_name = other.m_name;
				m_result = other.m_result;
				m_run_count = other.m_run_count;
			}

			TRACE_EXIT();
			return *this;
		}

		std::string 
		_test::get_name(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);
			TRACE_EXIT();
			return m_name;
		}

		test_result 
		_test::get_result(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);
			TRACE_EXIT_MESSAGE("%s", TEST_RESULT_STRING(m_result).c_str());
			return m_result;
		}

		bool 
		_test::is_result_valid(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);

			result = (m_run_count > 0);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		test_result 
		_test::run(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);
			
			setup_test(context, length);
			m_result = run_test(context, length);
			++m_run_count;
			teardown_test(context, length);

			TRACE_EXIT_MESSAGE("%s", TEST_RESULT_STRING(m_result).c_str());
			return m_result;
		}

		void 
		_test::reset(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);

			m_result = TEST_RESULT_INCONCLUSIVE;
			m_run_count = 0;

			TRACE_EXIT();
		}

		void 
		_test::set_name(
			__in const std::string &name
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);

			if(name.empty()) {
				TRACE_ERROR("%s", TEST_EXCEPTION_STRING(TEST_EXCEPTION_INVALID_NAME).c_str());
				THROW_TEST_EXCEPTION(TEST_EXCEPTION_INVALID_NAME);
			}

			m_name = name;

			TRACE_EXIT();
		}

		std::string 
		_test::to_string(
			__in bool show_only_failures,
			__in bool verbose
			)
		{
			std::stringstream stream;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_lock);
			UNREFERENCED_PARAMETER(verbose);

			if(!show_only_failures || ((m_result == TEST_RESULT_FAILURE) || (m_result == TEST_RESULT_INCONCLUSIVE))) {
				stream << "[" << TEST_RESULT_STRING(m_result);

				if(!m_run_count) {
					stream << " (INVALID)";
				}

				stream << "] " << m_name;
			}

			TRACE_EXIT();
			return stream.str();
		}
	}
}
