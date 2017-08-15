# CMake generated Testfile for 
# Source directory: /gscratch/mmcches/StrideSearch/cpp/lpmCxx/tests
# Build directory: /gscratch/mmcches/StrideSearch/cpp/lpmCxx/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(xyzVecTest "lpmXyzVectorUnitTest.exe")
ADD_TEST(outputMessageTest "lpmOutputMessageUnitTest.exe")
ADD_TEST(loggerTest "COMMAND" "mpirun" "-np" "2" "lpmLoggerUnitTest.exe")
ADD_TEST(coordsTest "lpmCoordsUnitTest.exe")
ADD_TEST(fieldTest "lpmFieldUnitTest.exe")
ADD_TEST(edgeTest "lpmEdgesUnitTest.exe")
ADD_TEST(faceTest "lpmFacesUnitTest.exe")
ADD_TEST(meshSeedUnitTest "lpmMeshSeedUnitTest.exe")
ADD_TEST(polymesh2dUnitTest "lpmPolyMeshUnitTest.exe")
ADD_TEST(mpiReplicatedDataUnitTest "COMMAND" "mpirun" "-np" "2" "lpmMPIReplicatedDataUnitTest.exe")
ADD_TEST(timerUnitTest "COMMAND" "mpirun" "-np" "2" "lpmTimerUnitTest.exe")
ADD_TEST(poissonSolver "COMMAND" "mpirun" "-np" "4" "lpmPoissonSolver.exe")
SET_TESTS_PROPERTIES(poissonSolver PROPERTIES  TIMEOUT "300")
ADD_TEST(octreeUnitTest "COMMAND" "mpirun" "-np" "1" "lpmOctreeUnitTest.exe")
ADD_TEST(taylorSeries3dTest "COMMAND" "mpirun" "-np" "1" "lpmTaylorSeries3dUnitTest.exe")
ADD_TEST(multiIndexTest "COMMAND" "mpirun" "-np" "1" "lpmMultiIndexUnitTest.exe")
ADD_TEST(treeSumTest "COMMAND" "mpirun" "-np" "1" "lpmTreeSumTest.exe")
