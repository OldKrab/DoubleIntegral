cmake_minimum_required(VERSION 3.19)
project(DoubleIntegral)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoubleIntegral main.cpp headers/PolygonDrawing.h source/geometry.cpp source/Spline.cpp source/ApproximationBase.cpp source/PolygonDrawing.cpp source/matrix.cpp source/SimpsonIntegral.cpp headers/SimpsonIntegral.h source/MonteCarloIntegral.cpp headers/MonteCarloIntegral.h)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_ROOT "D:/GoogleDrive/sync/source/library/SFML-2.5.1")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(DoubleIntegral sfml-graphics sfml-audio)


