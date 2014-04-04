# SCE
### Smart Chat Entity

A fairly basic C++ chat bot; currently running on IRC with hopes of adding XMPP
and JIM socket support.

This is an expansion of a previous work titled NICE which I've abandoned do to
the name being used for other projects.

There is a substantial amount of code pertaining to IRC and socket handling
taken from https://github.com/Fredi/IRCClient, while I do need to update some of
the files I have the full intention of keeping this project in-line with the
license requirements of the aforementioned IRCClient.

---

Requirements:

* Linux only currently.

* CMake compatible C++ compiler (tested w/ gcc 4.8).

* CMake (tested w/ 2.8).

After installing cmake run the following to create a build/out directory and
perform an out-of-source build.

	mkdir build
	cd build
	cmake ../
	make

Known Bugs:

	In most cases the prompt for the local terminal is burried by cout, while
	typing commands still works it would be nice if this could be displayed at
	the bottom constantly (ncurses terminal maybe?).
