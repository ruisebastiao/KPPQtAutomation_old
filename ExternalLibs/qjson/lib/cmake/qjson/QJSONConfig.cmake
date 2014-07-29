GET_FILENAME_COMPONENT(myDir ${CMAKE_CURRENT_LIST_FILE} PATH)

SET(QJSON_LIBRARIES qjson)
SET(QJSON_INCLUDE_DIR "E:/Projectos/Programming/qt/qjson-master/build/_preferred_path_/include")

include(${myDir}/QJSONTargets.cmake)
