cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME tomlplusplus)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

# set the timestamps of extracted contents to the time of extraction
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
        ${LIBRARY_NAME}
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG        v3.3.0
)
FetchContent_MakeAvailable(${LIBRARY_NAME})
FetchContent_GetProperties(${LIBRARY_NAME})

message(STATUS "${LIBRARY_NAME} is available now")
