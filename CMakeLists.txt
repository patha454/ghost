CMAKE_MINIMUM_REQUIRED(VERSION 3.13)


PROJECT(ghost_project C ASM)

MESSAGE(STATUS "Target CPU: ${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE(STATUS "Target OS: ${CMAKE_SYSTEM_NAME}")

IF(NOT EXISTS "${CMAKE_SOURCE_DIR}/printf")
    MESSAGE(FATAL_ERROR "Printf submodule not found. Try `git submodule update --init`.")
ELSE()
    MESSAGE(STATUS "Printf submodule found")
ENDIF()

ADD_LIBRARY(printf_lib STATIC
    printf/printf.c
)

IF (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    TARGET_COMPILE_OPTIONS(printf_lib PRIVATE
    # Sack protection causes seg faults.
    # It assumes %fs points to usable memory.
    "SHELL:-fno-stack-protector"
    "SHELL:-fvisibility=hidden"
    "SHELL:-fPIC"
    )
ELSEIF (CMAKE_C_COMPILER_ID STREQUAL "Clang")
TARGET_COMPILE_OPTIONS(printf_lib PRIVATE
    # Sack protection causes seg faults.
    # It assumes %fs points to usable memory.
    "SHELL:-fno-stack-protector"
    "SHELL:-fPIC"
    "SHELL:-fvisibility=hidden"
    )
ELSE ()
    MESSAGE(FATAL_ERROR "ghost: printf_lib: Unknown C compiler.")
ENDIF()

TARGET_INCLUDE_DIRECTORIES(printf_lib INTERFACE printf)

ADD_LIBRARY(ghost_app SHARED)
SET_TARGET_PROPERTIES(ghost_app PROPERTIES OUTPUT_NAME "ghost")
SET_TARGET_PROPERTIES(ghost_app PROPERTIES C_STANDARD 90)

TARGET_LINK_LIBRARIES(ghost_app PRIVATE printf_lib)

TARGET_INCLUDE_DIRECTORIES(ghost_app PRIVATE include)

# Enable full compiler warnings.
IF (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # Disable C11 deprecation warnings.
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    # Compile as C89 with warnings as errors.
    TARGET_COMPILE_OPTIONS(ghost_app PRIVATE
        "SHELL:-Za"
        "SHELL:-W3"
        "SHELL:-WX"
    )
ELSEIF (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # Compile as C90 with warnings as errors.
    TARGET_COMPILE_OPTIONS(ghost_app PRIVATE 
        "SHELL:-W" 
        "SHELL:-Wall"
        "SHELL:-Wpedantic"
        "SHELL:-Wextra"
        "SHELL:-Werror"
        "SHELL:-std=c90"
        "SHELL:-fno-stack-protector"
        "SHELL:-fvisibility=hidden"
        "SHELL:-fPIC"
)
ELSEIF (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    TARGET_COMPILE_OPTIONS(ghost_app PRIVATE 
        "SHELL:-W" 
        "SHELL:-Wall"
        "SHELL:-Wpedantic"
        "SHELL:-Wextra"
        "SHELL:-Werror"
        "SHELL:-Wno-unused-command-line-argument"
        "SHELL:-std=c90"
        "SHELL:-mstackrealign"
        "SHELL:-fno-stack-protector"
        "SHELL:-fPIC"
        "SHELL:-fvisibility=hidden"
    )
    TARGET_COMPILE_OPTIONS(printf_lib PRIVATE
        "SHELL:-mstackrealign"
    )
ELSE()
    MESSAGE(WARNING "Ghost: Unknown C compiler. Strict errors and warnings not enabled.")
ENDIF()



target_link_options(ghost_app PRIVATE
    "LINKER:-e,__start"
    "-nostdlib"
    "-ffreestanding"
    "LINKER:-static"
)

ADD_SUBDIRECTORY(src)
