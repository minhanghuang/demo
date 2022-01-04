###############################################################################
# Extract version numbers from version string
################################################################################
function (version_numbers version major minor patch)
  if (version MATCHES "([0-9]+)(\\.[0-9]+)?(\\.[0-9]+)?(rc[1-9][0-9]*|[a-z]+)?")
    if (CMAKE_MATCH_1)
      set (_major ${CMAKE_MATCH_1})
    else ()
      set (_major 0)
    endif ()
    if (CMAKE_MATCH_2)
      set (_minor ${CMAKE_MATCH_2})
      string (REGEX REPLACE "^\\." "" _minor "${_minor}")
    else ()
      set (_minor 0)
    endif ()
    if (CMAKE_MATCH_3)
      set (_patch ${CMAKE_MATCH_3})
      string (REGEX REPLACE "^\\." "" _patch "${_patch}")
    else ()
      set (_patch 0)
    endif ()
  else ()
    set (_major 0)
    set (_minor 0)
    set (_patch 0)
  endif ()
  set ("${major}" "${_major}" PARENT_SCOPE)
  set ("${minor}" "${_minor}" PARENT_SCOPE)
  set ("${patch}" "${_patch}" PARENT_SCOPE)
endfunction ()

function (trunk_make_package PACKAGE_NAME PACKAGE_VERSION PACKAGE_DESCRIPTION)
  version_numbers(${PACKAGE_VERSION}
    PACKAGE_VERSION_MAJOR
    PACKAGE_VERSION_MINOR
    PACKAGE_VERSION_PATCH
    )

  ##################################################################################
  # packaging
  #####################################################################################
  # default package generators
  if (APPLE)
    set (PACKAGE_GENERATOR        "PackageMaker")
    set (PACKAGE_SOURCE_GENERATOR "TGZ;ZIP")
  elseif (UNIX)
    set (PACKAGE_GENERATOR        "DEB") # RPM
    set (PACKAGE_SOURCE_GENERATOR "TGZ;ZIP")
  else ()
    set (PACKAGE_GENERATOR        "ZIP")
    set (PACKAGE_SOURCE_GENERATOR "ZIP")
  endif ()

  # used package generators
  set (CPACK_GENERATOR "${PACKAGE_GENERATOR}" CACHE STRING "List of binary package generators (CPack).")
  set (CPACK_SOURCE_GENERATOR "${PACKAGE_SOURCE_GENERATOR}" CACHE STRING "List of source package generators (CPack).")
  mark_as_advanced (CPACK_GENERATOR CPACK_SOURCE_GENERATOR)

  # some package generators (e.g., PackageMaker) do not allow .md extension
  configure_file ("${CMAKE_CURRENT_LIST_DIR}/README.md" "${CMAKE_CURRENT_BINARY_DIR}/README.txt" COPYONLY)

  # common package information
  set (CPACK_PACKAGE_VENDOR              "trunk")
  set (CPACK_PACKAGE_CONTACT             "cater@trunk.tech")
  set (CPACK_PACKAGE_NAME                "${PACKAGE_NAME}")
  set (CPACK_PACKAGE_VERSION             "${PACKAGE_VERSION}")
  set (CPACK_PACKAGE_VERSION_MAJOR       "${PACKAGE_VERSION_MAJOR}")
  set (CPACK_PACKAGE_VERSION_MINOR       "${PACKAGE_VERSION_MINOR}")
  set (CPACK_PACKAGE_VERSION_PATCH       "${PACKAGE_VERSION_PATCH}")
  set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PACKAGE_DESCRIPTION}")
  set (CPACK_RESOURCE_FILE_WELCOME       "${CMAKE_CURRENT_BINARY_DIR}/README.txt")
  set (CPACK_RESOURCE_FILE_LICENSE       "${CMAKE_CURRENT_LIST_DIR}/COPYING.txt")
  set (CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_CURRENT_BINARY_DIR}/README.txt")
  set (CPACK_INSTALL_PREFIX              "${CMAKE_INSTALL_PREFIX}")
  set (CPACK_OUTPUT_FILE_PREFIX          packages)
  set (CPACK_PACKAGE_RELOCATABLE         TRUE)
  set (CPACK_MONOLITHIC_INSTALL          TRUE)

  # RPM package information -- used in cmake/package.cmake.in also for DEB
  set (CPACK_RPM_PACKAGE_GROUP   "Development/Libraries")
  set (CPACK_RPM_PACKAGE_LICENSE "BSD")
  set (CPACK_RPM_PACKAGE_URL     "${PACKAGE_URL}")
  set (CPACK_RPM_CHANGELOG_FILE  "${CMAKE_CURRENT_LIST_DIR}/ChangeLog.txt")

  # if (INSTALL_HEADERS)
  #   set (CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_LIST_DIR}/doc/index.html")
  # else ()
  #   set (CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_LIST_DIR}/cmake/README_runtime.txt")
  # endif ()

  set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

  # system/architecture
  if (WINDOWS)
    if (CMAKE_CL_64)
      set (CPACK_SYSTEM_NAME "win64")
    else ()
      set (CPACK_SYSTEM_NAME "win32")
    endif ()
    set (CPACK_PACKAGE_ARCHITECTURE)
  elseif (APPLE)
    set (CPACK_PACKAGE_ARCHITECTURE darwin)
  else ()
    string (TOLOWER "${CMAKE_SYSTEM_NAME}" CPACK_SYSTEM_NAME)
    if (CMAKE_CXX_FLAGS MATCHES "-m32")
      set (CPACK_PACKAGE_ARCHITECTURE i386)
    else ()
      execute_process (
        COMMAND         dpkg --print-architecture
        RESULT_VARIABLE RV
        OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE
        )
      if (RV EQUAL 0)
	    string (STRIP "${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_ARCHITECTURE)
      else ()
        execute_process (COMMAND uname -m OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE)
        if (CPACK_PACKAGE_ARCHITECTURE MATCHES "x86_64")
	      set (CPACK_PACKAGE_ARCHITECTURE amd64)
        else ()
          set (CPACK_PACKAGE_ARCHITECTURE i386)
        endif ()
      endif ()
    endif ()
  endif ()

  # source package settings
  set (CPACK_SOURCE_TOPLEVEL_TAG      "source")
  set (CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
  set (CPACK_SOURCE_IGNORE_FILES      "/\\\\.git/;\\\\.swp$;\\\\.#;/#;\\\\.*~;cscope\\\\.*;/[Bb]uild[.+-_a-zA-Z0-9]*/")

  # default binary package settings
  set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY TRUE)
  set (CPACK_PACKAGE_FILE_NAME          "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
  if (CPACK_PACKAGE_ARCHITECTURE)
    set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${CPACK_PACKAGE_ARCHITECTURE}")
  endif ()

  # generator specific configuration file
  #
  # allow package maintainers to use their own configuration file
  # $ cmake -DCPACK_PROJECT_CONFIG_FILE:FILE=/path/to/package/config
  if (NOT CPACK_PROJECT_CONFIG_FILE)
    configure_file (
      "${CMAKE_CURRENT_LIST_DIR}/cmake/package.cmake.in"
      "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-package.cmake" @ONLY
      )
    set (CPACK_PROJECT_CONFIG_FILE "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-package.cmake")
  endif ()

  include (CPack)
endfunction()
