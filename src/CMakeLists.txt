# CMake source folder
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# Add source files to target
target_sources(ivex PRIVATE
  Input.cpp
  ivex.cpp
  Data.cpp
  Output.cpp
  IV.cpp
  Extraction.cpp
)
