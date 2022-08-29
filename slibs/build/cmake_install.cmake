# Install script for directory: /home/gant/DELILA-main/Components/slibs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/gant/DELILA-main/Components/slibs")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gant/DELILA-main/Components/slibs" TYPE SHARED_LIBRARY FILES "/home/gant/DELILA-main/Components/slibs/build/lib_cont_2718.so")
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_2718.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gant/DELILA-main/Components/slibs" TYPE SHARED_LIBRARY FILES "/home/gant/DELILA-main/Components/slibs/build/lib_cont_SISeth.so")
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_cont_SISeth.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gant/DELILA-main/Components/slibs" TYPE SHARED_LIBRARY FILES "/home/gant/DELILA-main/Components/slibs/build/lib_dev_MADC32.so")
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MADC32.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gant/DELILA-main/Components/slibs" TYPE SHARED_LIBRARY FILES "/home/gant/DELILA-main/Components/slibs/build/lib_dev_MTDC32.so")
  if(EXISTS "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gant/DELILA-main/Components/slibs/lib_dev_MTDC32.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/gant/DELILA-main/Components/slibs/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
