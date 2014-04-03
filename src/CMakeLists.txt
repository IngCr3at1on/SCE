set(SOURCES
	main.cpp
)

add_executable(sce ${SOURCES})

target_link_libraries(sce
	SCE
)
