# https://cmake.org/cmake/help/latest/module/CPack.html
include(InstallRequiredSystemLibraries) # include any runtime libraries that are needed by the project for the current platform

# Set some basic information about the project
set(CPACK_PACKAGE_NAME "R-Type")
set(CPACK_PACKAGE_CONTACT "Alwyn974")
set(CPACK_PACKAGE_VENDOR "Alwyn974")
set(CPACK_PACKAGE_DESCRIPTION "R-Type is a 2D space shooter game, in network mode, with a lot of different weapons and enemies.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "R-Type is a 2D space shooter game, in network mode, with a lot of different weapons and enemies.")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")

#[[get_target_property(TARGET_TYPE ${BINARY_NAME} TYPE)
if (TARGET_TYPE STREQUAL STATIC_LIBRARY)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-static-${CMAKE_SYSTEM_NAME}") # Static
elseif (TARGET_TYPE STREQUAL SHARED_LIBRARY)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-shared-${CMAKE_SYSTEM_NAME}") # Shared
endif ()]]

# Set the version information
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Set some resource files
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}") # Installation directory on the target system
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/rtype/icons/logo.ico") # Location of an icon to display during the installation process
set(CPACK_PACKAGE_CHECKSUM "SHA256") # Create a checksum for the package
set(CPACK_MONOLITHIC_INSTALL OFF) # Install all components in one package, can be useful to force the installation of all components

set(CPACK_PACKAGE_EXECUTABLES
        "r-type_server.exe" "R-Type Server"
        "r-type_client.exe" "R-Type Client"
) # Set the executables name

# Components
include(CPackComponent)
cpack_add_install_type(Full DISPLAY_NAME "Everything")
#cpack_add_install_type(Developer DISPLAY_NAME "Development")
cpack_add_install_type(Software DISPLAY_NAME "Software")

#cpack_add_component(headers
#        DISPLAY_NAME "Headers"
#        DESCRIPTION "C++ Header files"
#        GROUP "Development"
#        INSTALL_TYPES Developer Full
#)
#cpack_add_component(archive
#        DISPLAY_NAME "Archive"
#        DESCRIPTION "Static library"
#        GROUP "Development"
##        DEPENDS headers
#        INSTALL_TYPES Full
#)
#cpack_add_component(cmake
#        DISPLAY_NAME "CMake"
#        DESCRIPTION "CMake files"
#        GROUP "Development"
#        DEPENDS headers archive
#        INSTALL_TYPES Developer Full
#)
cpack_add_component(library
        DISPLAY_NAME "Library"
        DESCRIPTION "Shared library"
        GROUP "Software"
        INSTALL_TYPES Developer Full Software
)
cpack_add_component(runtime
        DISPLAY_NAME "Runtime"
        DESCRIPTION "Runtime files"
        GROUP "Software"
        INSTALL_TYPES Full Software
        REQUIRED
)
cpack_add_component_group(Software
        EXPANDED
        DESCRIPTION  "All of the tools you'll ever need to run software"
)
cpack_add_component_group(Development
        EXPANDED
        DESCRIPTION "All of the tools you'll ever need to develop software"
)

#get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
#list(REMOVE_ITEM CPACK_COMPONENTS_ALL "devel" "headers" "cmake" "archive")
set(CPACK_COMPONENTS_ALL "runtime" "Unspecified")

# Source package generator
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "7Z;DEB;IFW;NSIS;NSIS64;NUGET;STGZ:TGZ;TXZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES ".git;build;out;dist;cmake-*;include;lib")

include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackDEB.cmake) # DEB
include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackNSIS.cmake) # NSIS
include(${CMAKE_SOURCE_DIR}/cmake/cpack/CPackRPM.cmake) # RPM

include(CPack)
