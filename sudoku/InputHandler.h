#pragma once

#include "stdafx.h"

using namespace std;

class InputHandler {
public:
	void check(int argc, char **argv);

private:
	int isNum(const string &s);
};

