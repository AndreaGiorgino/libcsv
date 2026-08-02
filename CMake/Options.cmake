option(DEBUG "Enable debug build." OFF)
option(CSV_BUILD_TESTING "Enable testing and build tests." OFF)

if(DEBUG)
    add_compile_definitions(DEBUG)
    add_compile_options(-g -ggdb -O0)
endif()

if(CSV_BUILD_TESTING)
    enable_testing()
    add_subdirectory(CTest)
endif()
