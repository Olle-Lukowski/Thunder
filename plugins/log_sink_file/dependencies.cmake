set(PLUGIN_log_sink_file_DEPENDENCIES log)

if (WIN32)
  list(APPEND PLUGIN_log_sink_file_DEPENDENCIES pthread_win32)
endif()
