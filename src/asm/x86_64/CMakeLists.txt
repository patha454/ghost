IF ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    TARGET_SOURCES(ghost_app PRIVATE linux.s)
ELSE()
    MESSAGE(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}: ${CMAKE_SYSTEM_NAME} is not supported by Ghost.")
ENDIF()

TARGET_SOURCES(ghost_app PRIVATE
    arch.s
)
