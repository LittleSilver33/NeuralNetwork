cmake_minimum_required(VERSION 3.10)

# Project name
project(NeuralNetwork)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify ARM architecture if necessary
set(CMAKE_OSX_ARCHITECTURES arm64)

# Find Protobuf package
find_package(Protobuf REQUIRED)

# Add the Protobuf include directories
include_directories(${Protobuf_INCLUDE_DIRS})

# Generate C++ source files from .proto files
set(PROTO_FILES ${CMAKE_SOURCE_DIR}/proto/feedforward.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Find Abseil package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ABSL REQUIRED absl_status absl_strings absl_base absl_synchronization absl_log absl_check absl_raw_logging_internal absl_time)

# Add Abseil include directories
include_directories(${ABSL_INCLUDE_DIRS})
include_directories(/usr/local/include)
link_directories(${ABSL_LIBRARY_DIRS})

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add the test executables
add_executable(MatrixTest test/MatrixTest.cc Matrix.cc Matrix.h ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(NeuralNetworkTest test/NeuralNetworkTest.cc NeuralNetwork.cc NeuralNetwork.h ${PROTO_SRCS} ${PROTO_HDRS})

# Link Protobuf, Abseil, and GoogleTest libraries
target_link_libraries(MatrixTest ${Protobuf_LIBRARIES}
                                  ${ABSL_LIBRARIES}
                                  gtest
                                  gtest_main)

target_link_libraries(NeuralNetworkTest ${Protobuf_LIBRARIES}
                                         ${ABSL_LIBRARIES}
                                         gtest
                                         gtest_main)

# Include directories for generated protobuf files and Matrix header
target_include_directories(MatrixTest PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(NeuralNetworkTest PRIVATE ${CMAKE_SOURCE_DIR})

# Enable Testing
enable_testing()

# Add your tests to CTest
add_test(NAME MatrixTest COMMAND MatrixTest)
add_test(NAME NeuralNetworkTest COMMAND NeuralNetworkTest)
