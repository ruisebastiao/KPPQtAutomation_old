#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qjson" for configuration "Debug"
set_property(TARGET qjson APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(qjson PROPERTIES
  IMPORTED_IMPLIB_DEBUG "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/lib/qjsond.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "Qt5::Core"
  IMPORTED_LOCATION_DEBUG "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/bin/qjsond.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS qjson )
list(APPEND _IMPORT_CHECK_FILES_FOR_qjson "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/lib/qjsond.lib" "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/bin/qjsond.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
