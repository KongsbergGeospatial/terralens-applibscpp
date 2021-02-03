# CMakeList.txt : CMake project for TLInput, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)
project (TLInput)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH 64)
else()
  set(ARCH 32)
endif()
set(TERRALENS_CORE_PATH $ENV{TLCORE_PATH} CACHE PATH "TerraLens Core release path")
if(TERRALENS_CORE_PATH STREQUAL "")
	set(TERRALENS_CORE_PATH ${CMAKE_SOURCE_DIR})
endif()

if(WIN32)
  if(MSVC_VERSION EQUAL 1600) # 10.0 (2010)
    set(VSVER 100)
    set(VSYEAR 2010)
  elseif(MSVC_VERSION EQUAL 1700) # 11.0 (2012)
    set(VSVER 110)
    set(VSYEAR 2012)
  elseif(MSVC_VERSION EQUAL 1800) # 12.0 (2013)
    set(VSVER 120)
    set(VSYEAR 2013)
  elseif(MSVC_VERSION EQUAL 1900) # 14.0 (2015)
    set(VSVER 140)
    set(VSYEAR 2015)
  elseif(MSVC_VERSION GREATER 1919)
    set(VSVER 142)
    set(VSYEAR 2019)
  elseif(MSVC_VERSION GREATER 1900)
    set(VSVER 141)
    set(VSYEAR 2017)
  endif()

  # TerraLens Core
  file(TO_CMAKE_PATH
    ${TERRALENS_CORE_PATH}/v${VSVER}_GL
    CORE_DIR_RELEASE)
  file(TO_CMAKE_PATH
	${CMAKE_SOURCE_DIR}/3rdParty/v${VSVER}
    THIRD_PARTY_DIR_RELEASE)

  if(ARCH EQUAL 64)
    set(CORE_DIR_RELEASE ${CORE_DIR_RELEASE}_x64)
	set(THIRD_PARTY_DIR_RELEASE ${THIRD_PARTY_DIR_RELEASE}_x64)
  endif()

  set(CORE_DIR_DEBUG ${CORE_DIR_RELEASE}_d)
  set(THIRD_PARTY_DIR_DEBUG ${THIRD_PARTY_DIR_RELEASE}_d)

  set(CORE_3P_DIR_DEBUG ${CORE_DIR_DEBUG}/3rdParty)
  set(CORE_3P_DIR_RELEASE ${CORE_DIR_RELEASE}/3rdParty)

  set(CORE_LIB_DIR_DEBUG ${CORE_DIR_DEBUG}/lib)
  set(CORE_LIB_DIR_RELEASE ${CORE_DIR_RELEASE}/lib)

  set(CORE_INCLUDE_DIR_DEBUG ${CORE_DIR_DEBUG}/include)
  set(CORE_INCLUDE_DIR_RELEASE ${CORE_DIR_RELEASE}/include)

  set(IVC_LIB_DEBUG ${CORE_LIB_DIR_DEBUG}/IVC.lib)
  set(IVC_LIB_RELEASE ${CORE_LIB_DIR_RELEASE}/IVC.lib)

  set(IVC_DLL_DEBUG ${CORE_LIB_DIR_DEBUG}/IVC.dll)
  set(IVC_DLL_RELEASE ${CORE_LIB_DIR_RELEASE}/IVC.dll)

endif(WIN32)

if (UNIX)

  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Debug or Release" FORCE)
  endif(NOT CMAKE_BUILD_TYPE)

  file(TO_CMAKE_PATH
    ${TERRALENS_CORE_PATH}/
    CORE_DIR_RELEASE)
  file(TO_CMAKE_PATH
        ${CMAKE_SOURCE_DIR}/3rdParty/
    THIRD_PARTY_DIR_RELEASE)

  set(CORE_3P_DIR_DEBUG ${CORE_DIR_DEBUG}/3rdParty)
  set(CORE_3P_DIR_RELEASE ${CORE_DIR_RELEASE}/3rdParty)

  set(CORE_LIB_DIR_DEBUG ${CORE_DIR_DEBUG}/lib)
  set(CORE_LIB_DIR_RELEASE ${CORE_DIR_RELEASE}/lib)

  set(CORE_INCLUDE_DIR_DEBUG ${CORE_DIR_DEBUG}/include)
  set(CORE_INCLUDE_DIR_RELEASE ${CORE_DIR_RELEASE}/include)

  set(IVC_LIB_DEBUG ${CORE_LIB_DIR_DEBUG}/libIVC.so)
  set(IVC_LIB_RELEASE ${CORE_LIB_DIR_RELEASE}/libIVC.so)

  set(IVC_DLL_DEBUG ${CORE_LIB_DIR_DEBUG}/libIVC.so)
  set(IVC_DLL_RELEASE ${CORE_LIB_DIR_RELEASE}/libIVC.so)

endif (UNIX)

add_definitions(-DICL_EXPORTS)

include_directories("../src" 
  "../include"
  $<$<CONFIG:Debug>:${CORE_INCLUDE_DIR_DEBUG}>
  $<$<CONFIG:Release>:${CORE_INCLUDE_DIR_RELEASE}> )

set(SRC_LIST "${CMAKE_SOURCE_DIR}/../src/TerraLens/InputControl.cpp" 
	"${CMAKE_SOURCE_DIR}/../src/TerraLens/MouseOrientate3D.cpp" 
	"${CMAKE_SOURCE_DIR}/../src/TerraLens/MousePan2D.cpp" 
	"${CMAKE_SOURCE_DIR}/../src/TerraLens/MousePan3D.cpp"
	"${CMAKE_SOURCE_DIR}/../src/TerraLens/WheelZoom2D.cpp"
	"${CMAKE_SOURCE_DIR}/../src/TerraLens/WheelZoom3D.cpp" )

add_library (TLInput SHARED ${SRC_LIST})
target_link_libraries(TLInput 
	$<$<CONFIG:Debug>:${IVC_LIB_DEBUG}>
    $<$<CONFIG:Release>:${IVC_LIB_RELEASE}> )

set_target_properties( TLInput
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

install(TARGETS TLInput DESTINATION lib/)
install(DIRECTORY include DESTINATION .
        FILES_MATCHING PATTERN "*.h")

