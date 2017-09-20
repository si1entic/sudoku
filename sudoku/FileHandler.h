#pragma once

#include "stdafx.h"

using namespace std;

class FileHandler {
public:
	void read(const string &outputPath);
	void write(const string &outputPath,string str);

};