cmake_minimum_required(VERSION 3.10)

project(genEAT)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(genEAT
    src/genEAT.cpp
)

# Windows specific settings
if(WIN32)
    target_compile_definitions(genEAT PRIVATE
        _CRT_SECURE_NO_WARNINGS
        UNICODE
        _UNICODE
    )
    
    # Link Windows system libraries
    target_link_libraries(genEAT PRIVATE
        kernel32
        user32
    )
endif()