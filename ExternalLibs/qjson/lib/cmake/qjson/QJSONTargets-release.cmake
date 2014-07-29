#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qjson" for configuration "Release"
set_property(TARGET qjson APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(qjson PROPERTIES
  IMPORTED_IMPLIB_RELEASE "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/lib/qjson.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "Qt5::Core"
  IMPORTED_LOCATION_RELEASE "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/bin/qjson.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS qjson )
list(APPEND _IMPORT_CHECK_FILES_FOR_qjson "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/lib/qjson.lib" "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/bin/qjson.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
