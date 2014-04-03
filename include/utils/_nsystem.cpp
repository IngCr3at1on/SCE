/**
 * NICE : Nearly Intelligible Communications Entity
 * 
 * Execute a system process and return stdout in a string.
 *
 * http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
 */
#include <string>
#include <iostream>
#include <stdio.h>

#include "_nsystem.h"

std::string _nsystem(char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	std::cout <<  result << std::endl;
	return result;
}
