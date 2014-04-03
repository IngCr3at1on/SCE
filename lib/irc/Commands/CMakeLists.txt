add_library(IRC_COMMANDS
	SHARED
	IRCCommandJoin.cpp
)

target_link_libraries(IRC_COMMANDS
	SCE_COMMANDS
)
