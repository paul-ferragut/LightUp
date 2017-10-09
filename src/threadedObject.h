//
//  SysCommand.h
//
//  Created by Brett Renfer on 2/22/12.
//

#pragma once
#include "ofThread.h"
#include "ofMain.h" 

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>

class SysCommand : private ofThread
{

public:

	ofEvent<string> commandComplete;

	void callCommand(string command) {
		cmd = command;
	//	cout << cmd << endl;
		stopThread();
		startThread();
	}

	// CALL THIS DIRECTLY FOR BLOCKING COMMAND
	// thanks to: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
	std::string exec(char* cmd) {
		FILE* pipe = _popen(cmd, "r");
		if (!pipe) return "ERROR";
		char buffer[128];
		std::string result = "";
		while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}
		_pclose(pipe);
		return result;
	}

private:
	void threadedFunction() {
		ofLog(OF_LOG_VERBOSE, "call " + cmd);
		string result = exec((char *)cmd.c_str());
		ofLog(OF_LOG_VERBOSE, "RESULT " + result);
		stopThread();
		ofNotifyEvent(commandComplete, result, this);
	}

	string cmd;
};