find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(ivex PUBLIC OpenMP::OpenMP_CXX)
endif()
