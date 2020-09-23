cmake_minimum_required(VERSION 2.8)

project(base CXX C) 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
message("Current build type is : ${CMAKE_BUILD_TYPE}")
message("path is  : ${PROJECT_SOURCE_DIR}")
message("sysmtem name is  : ${CMAKE_SYSTEM_NAME}")


# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules
)

# add definitions
include(DefinePlatformDefaults)

if (APPLE)
#include(FindAppKit)
#include(FindCoreFoundation)
#include(FindApplicationServices)
include(Apple)
endif()

if (UNIX)

add_definitions(-D__STDC_FORMAT_MACROS)

elseif(WIN32)
add_definitions(-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
add_definitions(-D_SCL_SECURE_NO_DEPRECATE)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DCERT_CHAIN_PARA_HAS_EXTRA_FIELDS)
add_definitions(-DNOMINMAX)
add_definitions(-D_UNICODE)
add_definitions(-D_CRT_RAND_S)
add_definitions(-D"USE_ASH=1")
add_definitions(-DWIN32)
add_definitions(-DCOMPONENT_BUILD)
add_definitions(-DBASE_IMPLEMENTATION)
endif()

# compiler flags.
if (UNIX)
    set(CMAKE_CXX_FLAGS
        -ggdb
        -Wall
        -Wextra 
        -Woverloaded-virtual
        -Wno-unused-parameter
        -Wno-missing-field-initializers 
    )
elseif(WIN32)
    set(CMAKE_CXX_FLAGS 
        /Zi 
        /nologo  
        /EHsc 
        /GS 
        /Gd 
        /GR 
        /GF 
        /fp:precise 
        /Zc:wchar_t 
        /Zc:forScope 
        /errorReport:queue
        /FC
        /W3 
        /WX- 
        /wd4351 /wd4355 /wd4396 /wd4503 /wd4819 /wd4100 /wd4121 /wd4125 
        /wd4127 /wd4130 /wd4131 /wd4189 /wd4201 /wd4238 /wd4244 /wd4245 
        /wd4310 /wd4428 /wd4481 /wd4505 /wd4510 /wd4512 /wd4530 /wd4610 
        /wd4611 /wd4701 /wd4702 /wd4706 /wd4018 /wd4091 /wd4996 /wd4251
    )

	if(${MSVC_VERSION} GREATER 1700)
		LIST(APPEND CMAKE_CXX_FLAGS
			/d2Zi+ 
			)
	endif()
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# for base build
include_directories(${PROJECT_SOURCE_DIR}/)

if (UNIX)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")
set(CMAKE_CXX_STANDARD 11)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SOURCES 
base/at_exit.cc
base/barrier_closure.cc
base/base64.cc
base/base_paths.cc
base/big_endian.cc
base/bind_helpers.cc
base/build_time.cc
base/callback_helpers.cc
base/callback_internal.cc
base/command_line.cc
base/cpu.cc
base/environment.cc
base/files/file_util.cc
base/guid.cc
base/hash.cc
base/ini_parser.cc
base/lazy_instance.cc
base/location.cc
base/logging.cc
base/md5.cc
base/path_service.cc
base/pending_task.cc
base/pickle.cc
base/platform_file.cc
base/rand_util.cc
base/scoped_native_library.cc
base/sha1_portable.cc
base/sha256.cc
base/supports_user_data.cc
base/system/sys_info.cc
base/task_runner.cc
base/thread_task_runner_handle.cc
base/sequenced_task_runner.cc
base/sequence_checker_impl.cc
base/run_loop.cc
base/values.cc
base/value_conversions.cc
base/version.cc
base/debug/alias.cc
base/debug/crash_logging.cc
base/debug/debugger.cc
base/debug/stack_trace.cc
base/debug/task_annotator.cc
base/files/file_enumerator.cc
base/files/file_path.cc
base/files/file_path_constants.cc
base/files/memory_mapped_file.cc
base/files/file.cc
base/files/file_tracing.cc
base/files/scoped_temp_dir.cc
base/json/json_file_value_serializer.cc
base/json/json_parser.cc
base/json/json_reader.cc
base/json/json_string_value_serializer.cc
base/json/json_writer.cc
base/json/string_escape.cc
base/memory/aligned_memory.cc
base/memory/discardable_memory.cc
base/memory/ref_counted.cc
base/memory/ref_counted_memory.cc
base/memory/singleton.cc
base/memory/weak_ptr.cc
base/process/kill.cc
base/process/launch.cc
base/process/process_iterator.cc
base/process/process_metrics.cc
base/profiler/alternate_timer.cc
base/profiler/tracked_time.cc
base/strings/latin1_string_conversions.cc
base/strings/nullable_string16.cc
base/strings/safe_sprintf.cc
base/strings/stringprintf.cc
base/strings/string_number_conversions.cc
base/strings/string_piece.cc
base/strings/string_split.cc
base/strings/string_util.cc
base/strings/string_util_constants.cc
base/strings/utf_offset_string_conversions.cc
base/strings/utf_string_conversions.cc
base/strings/utf_string_conversion_utils.cc
base/strings/pattern.cc
base/synchronization/lock.cc
base/third_party/dmg_fp/dtoa_wrapper.cc
base/third_party/dmg_fp/g_fmt.cc
base/third_party/icu/icu_utf.cc
base/third_party/nspr/prtime.cc
base/threading/non_thread_safe_impl.cc
base/threading/simple_thread.cc
base/threading/thread_checker_impl.cc
base/threading/thread_collision_warner.cc
base/threading/thread_id_name_manager.cc
base/threading/thread_local_storage.cc
base/threading/post_task_and_reply_impl.cc
base/threading/thread_restrictions.cc
base/threading/sequenced_worker_pool.cc
base/threading/thread.cc
base/time/clock.cc
base/time/default_clock.cc
base/time/default_tick_clock.cc
base/time/tick_clock.cc
base/time/time.cc
base/timer/elapsed_timer.cc
base/message_loop/message_loop.cc
base/message_loop/message_pump.cc
base/message_loop/message_pump_default.cc
base/message_loop/incoming_task_queue.cc
base/message_loop/message_loop_task_runner.cc
third_party/modp_b64/modp_b64.cc
)

#add headers
LIST(APPEND SOURCES
base/memory/singleton_ptr.h
)

if (WIN32)
    LIST(APPEND SOURCES
		base/base_paths_win.cc        
		base/files/file_util_win.cc
		base/file_version_info_win.cc
		base/system/sys_info_win.cc
		base/guid_win.cc
		base/logging_win.cc
		base/native_library_win.cc
		base/platform_file_win.cc
		base/rand_util_win.cc
		base/sync_socket_win.cc
		base/system/sys_info_win.cc
		base/debug/debugger_win.cc
		base/debug/stack_trace_win.cc
		base/files/file_win.cc
		base/files/file_util_win.cc
		base/files/file_enumerator_win.cc
		base/files/memory_mapped_file_win.cc
		base/memory/shared_memory_win.cc
		base/process/kill_win.cc
		base/process/launch_win.cc
		base/process/process_win.cc
		base/process/memory_win.cc
		base/process/process_handle_win.cc
		base/process/process_info_win.cc
		base/process/process_iterator_win.cc
		base/process/process_metrics_win.cc
		base/strings/sys_string_conversions_win.cc
		base/synchronization/condition_variable_win.cc
		base/synchronization/lock_impl_win.cc
		base/synchronization/waitable_event_win.cc
		base/memory/shared_memory_handle_win.cc
		base/threading/platform_thread_win.cc
		base/threading/thread_local_storage_win.cc
		base/threading/thread_local_win.cc
		base/time/time_win.cc
		base/win/enum_variant.cc
		base/win/event_trace_controller.cc
		base/win/event_trace_provider.cc
		base/win/i18n.cc
		base/win/iat_patch_function.cc
		base/win/iunknown_impl.cc
		base/win/message_window.cc
		base/win/registry.cc
		base/win/resource_util.cc
		base/win/scoped_bstr.cc
		base/win/scoped_handle.cc
		base/win/scoped_process_information.cc
		base/win/scoped_variant.cc
		base/win/startup_information.cc
		base/win/windows_version.cc
		base/win/win_util.cc
		base/win/wrapped_window_proc.cc
		base/win/pe_image.cc
		base/win/object_watcher.cc
		base/message_loop/message_pump_win.cc
    )
endif()

if (LINUX OR BSD OR APPLE)
	LIST(APPEND SOURCES
		base/native_library_posix.cc
		base/guid_posix.cc
		base/base_paths_posix.cc
		base/platform_file_posix.cc
		base/rand_util_posix.cc
		base/sync_socket_posix.cc
		base/system/sys_info_posix.cc
		base/debug/debugger_posix.cc
		base/debug/stack_trace_posix.cc
		base/files/file_enumerator_posix.cc
		base/files/memory_mapped_file_posix.cc
		base/files/file_posix.cc
		base/files/file_util_posix.cc
		base/files/scoped_file.cc
		base/memory/shared_memory_posix.cc
		base/posix/file_descriptor_shuffle.cc
		base/posix/global_descriptors.cc
		base/posix/safe_strerror.cc
		base/process/kill_posix.cc
		base/process/launch_posix.cc
		base/process/process_handle_posix.cc
		base/process/process_metrics_posix.cc
		base/process/process_posix.cc
		base/strings/sys_string_conversions_posix.cc
		base/strings/string16.cc		
		base/synchronization/condition_variable_posix.cc
		base/synchronization/lock_impl_posix.cc
		base/synchronization/waitable_event_posix.cc
		base/threading/platform_thread_posix.cc
		base/threading/thread_local_posix.cc
		base/threading/platform_thread_internal_posix.cc
		base/threading/thread_local_storage_posix.cc
		base/time/time_posix.cc
		base/nix/xdg_util.cc
		base/message_loop/message_pump_libevent.cc
		base/third_party/xdg_user_dirs/xdg_user_dir_lookup.cc
		base/third_party/dynamic_annotations/dynamic_annotations.c
    )
endif()

if(LINUX)
    LIST(APPEND SOURCES
		base/system/sys_info_linux.cc
		base/debug/proc_maps_linux.cc
		base/posix/unix_domain_socket_linux.cc
		base/process/internal_linux.cc
		base/process/memory_linux.cc
		base/process/process_handle_linux.cc
		base/process/process_info_linux.cc
		base/process/process_iterator_linux.cc
		base/process/process_linux.cc
		base/process/process_metrics_linux.cc
		base/threading/platform_thread_linux.cc
    )
endif()

if (APPLE)
    LIST(APPEND SOURCES
		base/base_paths_mac.mm
		base/native_library_mac.mm
		base/process/launch_mac.cc
		base/time/time_mac.cc
		base/message_loop/message_pump_mac.mm
		base/strings/sys_string_conversions_mac.mm
		base/threading/platform_thread_mac.mm
		base/mac/mach_logging.cc
		base/mac/foundation_util.mm
		base/mac/bundle_locations.mm
		base/mac/scoped_nsautorelease_pool.mm
		base/mac/scoped_mach_port.cc
		base/mac/call_with_eh_frame.cc
		base/mac/call_with_eh_frame_asm.S
		base/system/sys_info_mac.mm
		base/files/file_util_mac.mm
		base/process/process_handle_mac.cc
		base/process/process_iterator_mac.cc
		base/process/process_metrics_mac.cc
    )

list(REMOVE_ITEM SOURCES
		base/native_library_posix.cc
		base/strings/sys_string_conversions_posix.cc
		base/memory/shared_memory_posix.cc
		base/threading/platform_thread_internal_posix.cc
    )

endif()

if (FREEBSD)
    LIST(APPEND SOURCES
		base/system/sys_info_freebsd.cc
		base/process/process_handle_freebsd.cc
		base/process/process_iterator_freebsd.cc
		base/process/process_metrics_freebsd.cc
		base/threading/platform_thread_freebsd.cc
    )
endif()

if (OPENBSD)
    LIST(APPEND SOURCES
		base/system/sys_info_openbsd.cc
    )
endif()

if (WIN32)
    LIST(APPEND SOURCES
		base/atomicops.h
		base/atomicops_internals_atomicword_compat.h
		base/atomicops_internals_x86_msvc.h
		base/atomic_ref_count.h
		base/atomic_sequence_num.h
		base/at_exit.h
		base/auto_reset.h
		base/barrier_closure.h
		base/base64.h
		base/base_export.h
		base/base_paths.h
		base/base_paths_win.h
		base/big_endian.h
		base/bind.h
		base/bind_helpers.h
		base/bind_internal.h
		base/bind_internal_win.h
		base/bits.h
		base/build_time.h
		base/callback.h
		base/callback_forward.h
		base/callback_helpers.h
		base/callback_internal.h
		base/callback_list.h
		base/cancelable_callback.h
		base/command_line.h
		base/compiler_specific.h
		base/cpu.h
		base/critical_closure.h
		base/environment.h
		base/event_types.h
		base/file_descriptor_posix.h
		base/files/file_util.h
		base/file_version_info.h
		base/file_version_info_win.h
		base/format_macros.h
		base/guid.h
		base/hash.h
		base/id_map.h
		base/ini_parser.h
		base/lazy_instance.h
		base/location.h
		base/logging.h
		base/logging_win.h
		base/md5.h
		base/move.h
		base/native_library.h
		base/observer_list.h
		base/os_compat_android.h
		base/os_compat_nacl.h
		base/path_service.h
		base/pending_task.h
		base/pickle.h
		base/platform_file.h
		base/rand_util.h
		base/scoped_clear_errno.h
		base/scoped_native_library.h
		base/scoped_observer.h
		base/sha1.h
		base/sha256.h
		base/stl_util.h
		base/supports_user_data.h
		base/sync_socket.h
		base/sys_byteorder.h
		base/system/sys_info.h
		base/template_util.h
		base/tuple.h
		base/values.h
		base/value_conversions.h
		base/version.h
		base/containers/hash_tables.h
		base/containers/linked_list.h
		base/containers/mru_cache.h
		base/containers/scoped_ptr_hash_map.h
		base/containers/small_map.h
		base/containers/stack_container.h
		base/debug/alias.h
		base/debug/crash_logging.h
		base/debug/debugger.h
		base/debug/leak_annotations.h
		base/debug/leak_tracker.h
		base/debug/stack_trace.h
		base/files/dir_reader_fallback.h
		base/files/file_enumerator.h
		base/files/file_path.h
		base/files/memory_mapped_file.h
		base/files/scoped_temp_dir.h
		base/i18n/base_i18n_export.h
		base/i18n/bidi_line_iterator.h
		base/i18n/break_iterator.h
		base/i18n/case_conversion.h
		base/i18n/char_iterator.h
		base/i18n/file_util_icu.h
		base/i18n/i18n_constants.h
		base/i18n/icu_encoding_detection.h
		base/i18n/icu_string_conversions.h
		base/i18n/icu_util.h
		base/i18n/number_formatting.h
		base/i18n/rtl.h
		base/i18n/string_compare.h
		base/i18n/string_search.h
		base/i18n/time_formatting.h
		base/ios/device_util.h
		base/ios/ios_util.h
		base/ios/scoped_critical_action.h
		base/json/json_file_value_serializer.h
		base/json/json_parser.h
		base/json/json_reader.h
		base/json/json_string_value_serializer.h
		base/json/json_value_converter.h
		base/json/json_writer.h
		base/json/string_escape.h
		base/memory/aligned_memory.h
		base/memory/discardable_memory.h
		base/memory/linked_ptr.h
		base/memory/manual_constructor.h
		base/memory/raw_scoped_refptr_mismatch_checker.h
		base/memory/ref_counted.h
		base/memory/ref_counted_delete_on_message_loop.h
		base/memory/ref_counted_memory.h
		base/memory/scoped_policy.h
		base/memory/scoped_ptr.h
		base/memory/scoped_vector.h
		base/memory/shared_memory.h
		base/memory/singleton.h
		base/memory/singleton_objc.h
		base/memory/weak_ptr.h
		base/process/kill.h
		base/process/launch.h
		base/process/memory.h
		base/process/process.h
		base/process/process_handle.h
		base/process/process_info.h
		base/process/process_iterator.h
		base/process/process_metrics.h
		base/profiler/alternate_timer.h
		base/profiler/tracked_time.h
		base/strings/latin1_string_conversions.h
		base/strings/nullable_string16.h
		base/strings/safe_sprintf.h
		base/strings/string16.h
		base/strings/stringize_macros.h
		base/strings/stringprintf.h
		base/strings/string_number_conversions.h
		base/strings/string_piece.h
		base/strings/string_split.h
		base/strings/string_tokenizer.h
		base/strings/string_util.h
		base/strings/string_util_win.h
		base/strings/sys_string_conversions.h
		base/strings/utf_offset_string_conversions.h
		base/strings/utf_string_conversions.h
		base/strings/utf_string_conversion_utils.h
		base/synchronization/cancellation_flag.h
		base/synchronization/condition_variable.h
		base/synchronization/lock.h
		base/synchronization/lock_impl.h
		base/synchronization/spin_wait.h
		base/synchronization/waitable_event.h
		base/threading/non_thread_safe.h
		base/threading/non_thread_safe_impl.h
		base/threading/platform_thread.h
		base/threading/simple_thread.h
		base/threading/thread_checker.h
		base/threading/thread_checker_impl.h
		base/threading/thread_collision_warner.h
		base/threading/thread_id_name_manager.h
		base/threading/thread_local.h
		base/threading/thread_local_storage.h
		base/time/clock.h
		base/time/default_clock.h
		base/time/default_tick_clock.h
		base/time/tick_clock.h
		base/time/time.h
		base/timer/elapsed_timer.h
		base/win/enum_variant.h
		base/win/event_trace_consumer.h
		base/win/event_trace_controller.h
		base/win/event_trace_provider.h
		base/win/i18n.h
		base/win/iat_patch_function.h
		base/win/iunknown_impl.h
		base/win/message_window.h
		base/win/pe_image.h
		base/win/registry.h
		base/win/resource_util.h
		base/win/scoped_bstr.h
		base/win/scoped_comptr.h
		base/win/scoped_com_initializer.h
		base/win/scoped_co_mem.h
		base/win/scoped_gdi_object.h
		base/win/scoped_handle.h
		base/win/scoped_hdc.h
		base/win/scoped_hglobal.h
		base/win/scoped_process_information.h
		base/win/scoped_propvariant.h
		base/win/scoped_select_object.h
		base/win/scoped_variant.h
		base/win/startup_information.h
		base/win/windows_version.h
		base/win/win_util.h
		base/win/wrapped_window_proc.h
    )
endif()

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

source_group_by_dir(SOURCES)
add_library(base SHARED ${SOURCES})

link_directories(${PROJECT_BINARY_DIR}/bin)

if (WIN32)
        target_link_libraries(base Netapi32 PowrProf Setupapi Version Dbghelp Ws2_32 Shlwapi)
elseif (LINUX)
        target_link_libraries(base dl pthread)
elseif (APPLE)
	target_link_libraries(base dl pthread
				${LIBRARY_OUTPUT_PATH}/libevent.dylib
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/AppKit.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/ApplicationServices.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Carbon.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/CoreFoundation.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Foundation.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/IOKit.framework
				${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Security.framework
				)
elseif (BSD)
        target_link_libraries(base dl pthread execinfo)
endif()

if (MSVC)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.lib ${CMAKE_SOURCE_DIR}/../build/lib/${PROJECT_NAME}.lib
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.dll ${CMAKE_SOURCE_DIR}/../build/lib/${PROJECT_NAME}.dll

  #copy to examples bin directory
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.dll ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.dll
)
endif(MSVC)

# Add examples
###############################################################

add_executable(cmdline examples/cmdline.cc)
if (WIN32)
target_link_libraries(cmdline base)
else (WIN32)
target_link_libraries(cmdline base event)
endif(WIN32)

add_executable(logtest examples/log.cc)
if (WIN32)
target_link_libraries(logtest base)
else (WIN32)
target_link_libraries(logtest base event)
endif(WIN32)

add_executable(path examples/path.cc)
if (WIN32)
target_link_libraries(path base)
else (WIN32)
target_link_libraries(path base event)
endif(WIN32)

add_executable(file examples/file.cc)
if (WIN32)
target_link_libraries(file base)
else (WIN32)
target_link_libraries(file base event)
endif(WIN32)

add_executable(process examples/process_info.cc)
if (WIN32)
target_link_libraries(process base)
else (WIN32)
target_link_libraries(process base event)
endif(WIN32)

add_executable(string examples/string.cc)
if (WIN32)
target_link_libraries(string base)
else (WIN32)
target_link_libraries(string base event)
endif(WIN32)
###############################################################

