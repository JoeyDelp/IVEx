# CMakeLists for IVEx containing the ivex library
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(IVEx VERSION 0.1)

# CMake files
include(${PROJECT_SOURCE_DIR}/cmake/commit_hash.cmake)
add_definitions(-DVERSION="${CMAKE_PROJECT_VERSION}")

# Conanfile
include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Add executable
add_subdirectory(src)

# Minimum compiler requirements
target_compile_features(ivex PUBLIC cxx_std_17)

# Include directories
target_include_directories(ivex PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  /usr/local/include
)

# Library dependencies

find_library(JOSIM_LIB libjosim)

target_link_libraries(ivex $JOSIM_LIB)

# Link dependencies
# Testing
include(CTest)
enable_testing()
add_subdirectory(tests)

# Installation: Targets
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS ivex EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ivex::
  DESTINATION share/${PROJECT_NAME}/
)

write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Installation: Headers
install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/")
