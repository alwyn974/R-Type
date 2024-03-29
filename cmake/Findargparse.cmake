cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME argparse)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

# set the timestamps of extracted contents to the time of extraction
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT ${LIBRARY_NAME}_FOUND)
    FetchContent_Declare(
            ${LIBRARY_NAME}
            GIT_REPOSITORY https://github.com/p-ranav/argparse.git
            GIT_TAG v2.9
            GIT_SHALLOW 1 # Only fetch the head commit
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    FetchContent_GetProperties(${LIBRARY_NAME})
endif ()
