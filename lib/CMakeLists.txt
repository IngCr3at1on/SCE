add_subdirectory(Commands)
add_subdirectory(InternalCommands)

add_library(SCE
	SHARED
	IRCEval.cpp
	SCEEval.cpp
	SCESocket.cpp
)

target_link_libraries(SCE
	SCE_COMMANDS
	INTERNAL_COMMANDS
	COMMONUTILS
)
