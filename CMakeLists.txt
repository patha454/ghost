CMAKE_MINIMUM_REQUIRED(VERSION 3.13)


PROJECT(ghost_project C ASM)

MESSAGE(STATUS "Target CPU: ${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE(STATUS "Target OS: ${CMAKE_SYSTEM_NAME}")

ADD_EXECUTABLE(ghost_app)
SET_TARGET_PROPERTIES(ghost_app PROPERTIES OUTPUT_NAME "ghost")

TARGET_INCLUDE_DIRECTORIES(ghost_app PRIVATE include)

target_link_options(ghost_app PRIVATE
    "LINKER:-e,__start"
    "-nostdlib"
    "-ffreestanding"
    "-static"
)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(asm)
