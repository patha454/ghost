TARGET_SOURCES(ghost_app PRIVATE
    main.c
    string.c
)

ADD_SUBDIRECTORY(system_calls)
ADD_SUBDIRECTORY(auxv)
ADD_SUBDIRECTORY(asm)
