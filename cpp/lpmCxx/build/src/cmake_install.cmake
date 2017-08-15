# Install script for directory: /gscratch/mmcches/StrideSearch/cpp/lpmCxx/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmXyzVector.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmOutputMessage.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmLogger.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmCoords.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmEuclideanCoords.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmSphericalCoords.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmField.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmAnalyticFunctions.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmEdges.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmFaces.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmTriFaces.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmQuadFaces.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmMeshSeed.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmPolyMesh2d.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmVtkFileIO.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmParticles.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmMeshedParticles.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmMPIReplicatedData.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmTimer.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmMultiIndex.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmTaylorSeries3d.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmTreeSum.h"
    "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/src/LpmDirectSum.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/gscratch/mmcches/StrideSearch/cpp/lpmCxx/build/src/liblpm.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

