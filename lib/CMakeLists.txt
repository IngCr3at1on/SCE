add_subdirectory(Commands)
add_subdirectory(InternalCommands)

add_library(SCE
	SHARED
	IRCEval.cpp
	SCEBrain.cpp
	SCEEval.cpp
	SCESocket.cpp
	SCESocketHandler.cpp
	SCESocketIRC.cpp
)

target_link_libraries(SCE
	SCE_COMMANDS
	INTERNAL_COMMANDS
	COMMONUTILS
)
