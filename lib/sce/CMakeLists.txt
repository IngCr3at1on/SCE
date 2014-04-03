add_library(SCE
	SHARED
	SCEEval.cpp
	SCESocket.cpp
)

target_link_libraries(SCE
	SIMPLE_IRC_SOCKET
	IRC
	SCE_COMMANDS
)
