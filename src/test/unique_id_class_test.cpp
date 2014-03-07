/*
 * unique_id_class_test.cpp
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
#include "test.h"
#include "test_type.h"
#include "trace.h"
#include "unique_id_class.h"
#include "unique_id_class_test.h"

namespace NIMBLE_NS {

	namespace TEST_NS {
	
		static unique_id_class_test_assignment unique_id_class_test_0;
		static unique_id_class_test_destruction unique_id_class_test_1;
		static unique_id_class_test_get_id unique_id_class_test_2;
		static unique_id_class_test_get_reference_count unique_id_class_test_3;
		static unique_id_class_test_instantiation unique_id_class_test_4;
		static unique_id_class_test_is_unique unique_id_class_test_5;
		static unique_id_class_test_set_id unique_id_class_test_6;

		void 
		unique_id_class_register_tests(
			__inout test_suite &suite
			)
		{
			TRACE_ENTRY();

			suite.register_test(unique_id_class_test_0);
			suite.register_test(unique_id_class_test_1);
			suite.register_test(unique_id_class_test_2);
			suite.register_test(unique_id_class_test_3);
			suite.register_test(unique_id_class_test_4);
			suite.register_test(unique_id_class_test_5);
			suite.register_test(unique_id_class_test_6);

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_assignment::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				COMPONENT_NS::unique_id_class cls, cls2, cls3;
				
				cls = cls2;

				if((cls.get_id() != cls2.get_id()) || (cls.get_reference_count() != cls2.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				cls3 = COMPONENT_NS::unique_id_class(cls2);

				if((cls3.get_id() != cls2.get_id()) || (cls3.get_reference_count() != cls2.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				cls = COMPONENT_NS::unique_id_class(id);

				if((cls.get_id() != id) || (cls.get_reference_count() != 2)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_assignment::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_assignment::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_destruction::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				COMPONENT_NS::unique_id_class cls3;

				{
					COMPONENT_NS::unique_id_class cls;
					id = cls.get_id();
				}

				if(COMPONENT_NS::UNIQUE_ID_NS::is_registered(id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				{
					COMPONENT_NS::unique_id_class cls2;
					cls3 = cls2;

					if(cls3.get_reference_count() != 2) {
						TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
						result = TEST_RESULT_FAILURE;
						goto exit;
					}
				}

				if(!COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls3.get_id())
						|| (cls3.get_reference_count() != 1)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_destruction::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_destruction::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_get_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				COMPONENT_NS::unique_id_class cls, cls2;
				cls = cls2;

				if(!COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls.get_id())
						|| !COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls2.get_id())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(cls.get_id() != cls2.get_id()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_get_id::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_get_id::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_get_reference_count::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				COMPONENT_NS::unique_id_class cls, cls2;

				if(COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls.get_id()) != cls.get_reference_count()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				cls = cls2;

				if(COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls2.get_id()) != cls2.get_reference_count()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_get_reference_count::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_get_reference_count::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_instantiation::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				COMPONENT_NS::unique_id_class cls, cls2(id), cls3(cls2);

				if(!COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls.get_id())
						|| (COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls.get_id()) != cls.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(!COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls2.get_id())
						|| (COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls2.get_id()) != cls2.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if((cls3.get_id() != cls2.get_id())
						|| !COMPONENT_NS::UNIQUE_ID_NS::is_registered(cls3.get_id())
						|| (COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls3.get_id()) != cls3.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_instantiation::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_instantiation::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_is_unique::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				COMPONENT_NS::unique_id_class cls, cls2;
				
				cls.set_id(id, true);

				if(!cls.is_unique()
						|| !COMPONENT_NS::UNIQUE_ID_NS::is_unique(cls.get_id())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(cls2.is_unique()
						|| COMPONENT_NS::UNIQUE_ID_NS::is_unique(cls2.get_id())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				try {
					cls2 = cls;
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_is_unique::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_is_unique::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}

		test_result 
		_unique_id_class_test_set_id::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid id;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				COMPONENT_NS::unique_id_class cls, cls2;
				id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				cls.set_id(cls2.get_id());

				if((cls.get_id() != cls2.get_id())
						|| (cls.get_reference_count() != 2)
						|| (COMPONENT_NS::UNIQUE_ID_NS::get_reference_count(cls.get_id()) != cls.get_reference_count())) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				cls2.set_id(id, true);

				try {
					cls.set_id(cls2.get_id());
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				result = TEST_RESULT_SUCCESS;
			} catch(std::runtime_error &exc) {
#ifndef _DEBUG
				UNREFERENCED_PARAMETER(exc);
#endif // _DEBUG
				TRACE_ERROR("%s: %s", m_name.c_str(), exc.what());
				result = TEST_RESULT_INCONCLUSIVE;
			}

		exit:
			TRACE_EXIT_MESSAGE("[%s] %s", TEST_RESULT_STRING(result).c_str(), m_name.c_str());
			return result;
		}

		void 
		_unique_id_class_test_set_id::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(!COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::initialize();
			}

			TRACE_EXIT();
		}

		void 
		_unique_id_class_test_set_id::teardown_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			if(COMPONENT_NS::is_initialized()) {
				COMPONENT_NS::destroy();
			}

			TRACE_EXIT();
		}
	}
}
