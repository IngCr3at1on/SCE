add_subdirectory(Commands)

add_library(SCE
	SHARED
	IRCEval.cpp
	SCEEval.cpp
	SCESocket.cpp
	split.cpp
)

target_link_libraries(SCE
	SCE_COMMANDS
	COMMONUTILS
)
