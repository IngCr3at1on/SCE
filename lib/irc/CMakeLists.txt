add_subdirectory(Commands)

add_library(IRC
	SHARED
	IRCEval.cpp
)

target_link_libraries(IRC
	COMMONUTILS
	IRC_COMMANDS
)
