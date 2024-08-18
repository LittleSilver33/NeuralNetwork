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

# Add the Abseil directory
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/abseil")

# Find Abseil package
find_package(absl REQUIRED COMPONENTS base synchronization log check raw_logging_internal time status strings strings_internal)

# Add the Abseil include directories
include_directories(${absl_INCLUDE_DIRS})

# Add the Matrix test executable
add_executable(MatrixTest test/MatrixTest.cc Matrix.cc Matrix.h ${PROTO_SRCS} ${PROTO_HDRS})

# Link Protobuf, Abseil, and GoogleTest libraries
target_link_libraries(MatrixTest ${Protobuf_LIBRARIES}
                                  absl::base
                                  absl::synchronization
                                  absl::log
                                  absl::check
                                  absl::raw_logging_internal
                                  absl::time
                                  absl::status
                                  absl::strings
                                  absl::strings_internal
                                  gtest
                                  gtest_main)

# Include directories for generated protobuf files and Matrix header
target_include_directories(MatrixTest PRIVATE ${CMAKE_SOURCE_DIR})

# Enable Testing
enable_testing()

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add your tests to CTest
add_test(NAME MatrixTest COMMAND MatrixTest)