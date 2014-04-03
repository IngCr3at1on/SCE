/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2014, Nathan Bass

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************************
SCE (Smart Chat Entity, pronounced C).

Used for concept testing.
********************************************************************************
CORE, used to launch Console, Socket and Evaluation separately.
*******************************************************************************/

#include <iostream>
#include <pthread.h>

#include "SCE.hpp"

void *SCE::listen_console(void *dummy) {
	_console.input_prompt();
	/* Use returns from eval to determine when to end our loop (by changing
	 * the state of running). */
	running = _eval.read_input(_console.input, true);
}

int SCE::Init() {
	pthread_t listen1;
	bool sock;

	sock = false;
	running = true;

	// Start SCESocket (and all sub-sockets) during Console initialization.
	/*
	if(_socket.Init()) {
		
	}
	*/

	/* Send a status when starting the console so we know if socket access is
	 * available or just local. */
	_console.Init(sock);

	while(running) {
		pthread_create(&listen1, NULL, listen_console, NULL);

		//listen_l.join();
	}
	
	pthread_exit(NULL);
	return 0;
} // void SCE::init()
