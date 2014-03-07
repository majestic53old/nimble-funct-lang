/*
 * token_tree_test.cpp
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
#include "token_tree.h"
#include "token_tree_test.h"
#include "trace.h"
#include "unique_id.h"

namespace NIMBLE_NS {

	namespace TEST_NS {

		static token_tree_test_decrement_reference token_tree_test_0;
		static token_tree_test_destroy token_tree_test_1;
		static token_tree_test_get_node token_tree_test_2;
		static token_tree_test_get_reference_count token_tree_test_3;
		static token_tree_test_increment_reference token_tree_test_4;
		static token_tree_test_initialize token_tree_test_5;
		static token_tree_test_is_initialized token_tree_test_6;
		static token_tree_test_is_registered token_tree_test_7;
		static token_tree_test_register_node token_tree_test_8;
		static token_tree_test_registration_count token_tree_test_9;

		void 
		token_tree_register_tests(
			__inout test_suite &suite
			)
		{
			TRACE_ENTRY();

			suite.register_test(token_tree_test_0);
			suite.register_test(token_tree_test_1);
			suite.register_test(token_tree_test_2);
			suite.register_test(token_tree_test_3);
			suite.register_test(token_tree_test_4);
			suite.register_test(token_tree_test_5);
			suite.register_test(token_tree_test_6);
			suite.register_test(token_tree_test_7);
			suite.register_test(token_tree_test_8);
			suite.register_test(token_tree_test_9);

			TRACE_EXIT();
		}

		test_result 
		_token_tree_test_decrement_reference::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::increment_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id) != INITIAL_REFERENCE_COUNT) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id) != 0) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				if(COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
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
		_token_tree_test_decrement_reference::setup_test(
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
		_token_tree_test_decrement_reference::teardown_test(
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
		_token_tree_test_destroy::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				try {
					
					if(COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
						COMPONENT_NS::TOKEN_TREE_NS::destroy();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(NULL_UUID);
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::get_node(NULL_UUID);
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(NULL_UUID);
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::increment_reference(NULL_UUID);
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::registeration_count();
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				} catch(...) {}

				try {
					COMPONENT_NS::TOKEN_TREE_NS::register_node(NULL_UUID, NULL_UUID);
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
		_token_tree_test_destroy::setup_test(
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
		_token_tree_test_destroy::teardown_test(
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
		_token_tree_test_get_node::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node, ref_node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(!COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				ref_node = COMPONENT_NS::TOKEN_TREE_NS::get_node(node_id);

				if(ref_node != node) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				try {
					ref_node = COMPONENT_NS::TOKEN_TREE_NS::get_node(node_id);
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
		_token_tree_test_get_node::setup_test(
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
		_token_tree_test_get_node::teardown_test(
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
		_token_tree_test_get_reference_count::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::increment_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT + 1) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				try {
					COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id);
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
		_token_tree_test_get_reference_count::setup_test(
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
		_token_tree_test_get_reference_count::teardown_test(
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
		_token_tree_test_increment_reference::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::increment_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::get_reference_count(node_id) != INITIAL_REFERENCE_COUNT + 1) {
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
		_token_tree_test_increment_reference::setup_test(
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
		_token_tree_test_increment_reference::teardown_test(
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
		_token_tree_test_initialize::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				try {
					
					if(COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
						COMPONENT_NS::TOKEN_TREE_NS::destroy();
					}
				} catch(...) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				try {
					
					if(!COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
						COMPONENT_NS::TOKEN_TREE_NS::initialize();
					}
				} catch(...) {
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
		_token_tree_test_initialize::setup_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);
			TRACE_EXIT();
		}

		void 
		_token_tree_test_initialize::teardown_test(
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
		_token_tree_test_is_initialized::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				
				if(!COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::destroy();

				if(COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::initialize();

				if(!COMPONENT_NS::TOKEN_TREE_NS::is_initialized()) {
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
		_token_tree_test_is_initialized::setup_test(
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
		_token_tree_test_is_initialized::teardown_test(
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
		_token_tree_test_is_registered::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(!COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
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
		_token_tree_test_is_registered::setup_test(
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
		_token_tree_test_is_registered::teardown_test(
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
		_token_tree_test_register_node::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id;
			token_node node, ref_node;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(!COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				ref_node = COMPONENT_NS::TOKEN_TREE_NS::get_node(node_id);
				
				if(ref_node != node) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node_id, NULL_UUID);

				if(!COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				ref_node = COMPONENT_NS::TOKEN_TREE_NS::get_node(node_id);
				
				if(ref_node == node) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::is_registered(node_id)) {
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
		_token_tree_test_register_node::setup_test(
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
		_token_tree_test_register_node::teardown_test(
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
		_token_tree_test_registration_count::run_test(
			__in uintptr_t context,
			__in size_t length
			)
		{
			uuid node_id, node_id2;
			token_node node, node2;
			test_result result = TEST_RESULT_INCONCLUSIVE;

			TRACE_ENTRY();
			UNREFERENCED_PARAMETER(context);
			UNREFERENCED_PARAMETER(length);

			try {
				INITIALIZE_TOKEN_NODE(node);
				INITIALIZE_TOKEN_NODE(node2);
				node.id = COMPONENT_NS::UNIQUE_ID_NS::generate();
				node2.id = COMPONENT_NS::UNIQUE_ID_NS::generate();

				if(COMPONENT_NS::TOKEN_TREE_NS::registeration_count()) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				node_id = COMPONENT_NS::TOKEN_TREE_NS::register_node(node);

				if(COMPONENT_NS::TOKEN_TREE_NS::registeration_count() != 1) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				node_id2 = COMPONENT_NS::TOKEN_TREE_NS::register_node(node2);

				if(COMPONENT_NS::TOKEN_TREE_NS::registeration_count() != 2) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id);

				if(COMPONENT_NS::TOKEN_TREE_NS::registeration_count() != 1) {
					TRACE_ERROR("%s: %s", m_name.c_str(), TEST_RESULT_STRING(TEST_RESULT_FAILURE).c_str());
					result = TEST_RESULT_FAILURE;
					goto exit;
				}

				COMPONENT_NS::TOKEN_TREE_NS::decrement_reference(node_id2);

				if(COMPONENT_NS::TOKEN_TREE_NS::registeration_count()) {
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
		_token_tree_test_registration_count::setup_test(
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
		_token_tree_test_registration_count::teardown_test(
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
