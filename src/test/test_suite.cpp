/*
 * test_suite.cpp
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

#include "test_suite.h"
#include "test_suite_type.h"
#include "test_type.h"
#include "trace.h"

namespace NIMBLE_NS {

	#ifdef TRACE_FLAG
	#undef TRACE_FLAG
	#define TRACE_FLAG TRACE_FLAG_TEST
	#endif // TRACE_FLAG

	namespace TEST_NS {

		_test_suite::_test_suite(void)
		{
			TRACE_ENTRY();

			test_suite::reset();

			TRACE_EXIT();
		}

		_test_suite::_test_suite(
			__in const _test_suite &other
			) :
				m_run_count(other.m_run_count),
				m_test_map(other.m_test_map)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		_test_suite::~_test_suite(void)
		{
			TRACE_ENTRY();

			unregister_all_tests();

			TRACE_EXIT();
		}

		_test_suite &
		_test_suite::operator=(
			__in const _test_suite &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			if(this != &other) {
				unregister_all_tests();
				m_run_count = other.m_run_count;
				m_test_map = other.m_test_map;
			}

			TRACE_EXIT();
			return *this;
		}

		test &
		_test_suite::get_test(
			__in const std::string &name
			)
		{
			std::map<std::string, test &>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			test_iter = m_test_map.find(name);
			if(test_iter == m_test_map.end()) {
				TRACE_ERROR("%s: %s", TEST_SUITE_EXCEPTION_STRING(TEST_SUITE_EXCEPTION_UNKNOWN_TEST).c_str(), name.c_str());
				THROW_TEST_SUITE_EXCEPTION_MESSAGE(TEST_SUITE_EXCEPTION_UNKNOWN_TEST, "%s", name.c_str());
			}

			TRACE_EXIT();
			return test_iter->second;
		}

		size_t 
		_test_suite::get_test_count(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			result = m_test_map.size();

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		bool 
		_test_suite::has_test(
			__in const std::string &name
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			result = (m_test_map.find(name) != m_test_map.end());

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		void 
		_test_suite::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			std::srand((uint32_t) std::time(NULL));

			TRACE_EXIT();
		}

		bool 
		_test_suite::is_result_valid(void)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			result = (m_run_count > 0);

			TRACE_EXIT_MESSAGE("%i", result);
			return result;
		}

		void 
		_test_suite::reset(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			m_run_count = 0;

			TRACE_EXIT();
		}

		void 
		_test_suite::register_test(
			__in test &tst
			)
		{
			register_test(tst.get_name(), tst);
		}

		void 
		_test_suite::register_test(
			__in const std::string &name,
			__in test &tst
			)
		{
			std::string result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			if(m_test_map.find(name) != m_test_map.end()) {
				TRACE_ERROR("%s: %s", TEST_SUITE_EXCEPTION_STRING(TEST_SUITE_EXCEPTION_TEST_ALREADY_REGISTERED).c_str(), name.c_str());
				THROW_TEST_SUITE_EXCEPTION_MESSAGE(TEST_SUITE_EXCEPTION_TEST_ALREADY_REGISTERED, "%s", name.c_str());
			}

			m_test_map.insert(std::pair<std::string, test &>(name, tst));

			TRACE_EXIT();
		}

		size_t 
		_test_suite::run_all_tests(
			__in uintptr_t context,
			__in size_t length
			)
		{
			size_t result = 0;
			std::map<std::string, test &>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			for(test_iter = m_test_map.begin(); test_iter != m_test_map.end(); ++test_iter) {
				
				if(run_test(test_iter->first, context, length) == TEST_RESULT_SUCCESS) {
					++result;
				}
			}

			TRACE_EXIT_MESSAGE("%lu", result);
			return result;
		}

		test_result 
		_test_suite::run_test(
			__in const std::string &name,
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result;
			std::map<std::string, test &>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			if(!m_run_count) {
				test_suite::initialize();
			}

			test_iter = m_test_map.find(name);
			if(test_iter == m_test_map.end()) {
				TRACE_ERROR("%s: %s", TEST_SUITE_EXCEPTION_STRING(TEST_SUITE_EXCEPTION_TEST_NOT_REGISTERED).c_str(), name.c_str());
				THROW_TEST_SUITE_EXCEPTION_MESSAGE(TEST_SUITE_EXCEPTION_TEST_NOT_REGISTERED, "%s", name.c_str());
			}

			try {
				result = test_iter->second.run(context, length);
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s throw an exception: %s", name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			} catch(...) {
				TRACE_ERROR("%s throw an unknown exception", name.c_str());
				result = TEST_RESULT_INCONCLUSIVE;
			}

			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), name.c_str());
			return result;
		}

		std::string 
		_test_suite::to_string(
			__in bool verbose
			)
		{
			test_result result;
			std::stringstream stream;
			std::map<std::string, test &>::iterator test_iter;
			size_t failed = 0, inconclusive = 0, succeeded = 0;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			for(test_iter = m_test_map.begin(); test_iter != m_test_map.end(); ++test_iter) {
				
				if(!test_iter->second.is_result_valid()) {
					continue;
				}

				result = test_iter->second.get_result();
				switch(result) {
					case TEST_RESULT_FAILURE:
						++failed;
						break;
					case TEST_RESULT_INCONCLUSIVE:
						++inconclusive;
						break;
					case TEST_RESULT_SUCCESS:
						++succeeded;
						break;
					default:
						TRACE_ERROR("%s: %lu", TEST_SUITE_EXCEPTION_STRING(TEST_SUITE_EXCEPTION_UNKNOWN_TEST_RESULT).c_str(), result);
						THROW_TEST_SUITE_EXCEPTION_MESSAGE(TEST_SUITE_EXCEPTION_UNKNOWN_TEST_RESULT, "%lu", result);
				}
			}

			stream << "Test Count: " << m_test_map.size() << ", Pass Rate: " 
				<< (100.0 * ((succeeded) / (float) (succeeded + failed + inconclusive))) << "%";
			
			if(verbose) {
				stream << " (Succeeded: " << succeeded << ", Failed: " << failed << ", Inconclusive: " << inconclusive << ")";
			}

			for(test_iter = m_test_map.begin(); test_iter != m_test_map.end(); ++test_iter) {
				stream << std::endl << "--- " << test_iter->second.to_string(verbose);
			}

			TRACE_EXIT();
			return stream.str();
		}

		void 
		_test_suite::unregister_all_tests(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			while(!m_test_map.empty()) {
				unregister_test(m_test_map.begin()->first);
			}

			m_test_map.clear();

			TRACE_EXIT();
		}

		void 
		_test_suite::unregister_test(
			__in const std::string &name
			)
		{
			std::map<std::string, test &>::iterator test_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECURSIVE(m_test_suite_lock);

			test_iter = m_test_map.find(name);
			if(test_iter == m_test_map.end()) {
				TRACE_ERROR("%s: %s", TEST_SUITE_EXCEPTION_STRING(TEST_SUITE_EXCEPTION_TEST_NOT_REGISTERED).c_str(), name.c_str());
				THROW_TEST_SUITE_EXCEPTION_MESSAGE(TEST_SUITE_EXCEPTION_TEST_NOT_REGISTERED, "%s", name.c_str());
			}

			test_iter->second.reset();
			m_test_map.erase(test_iter);

			TRACE_EXIT();
		}
	}
}
