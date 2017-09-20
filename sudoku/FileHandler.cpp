#include "stdafx.h"
#include "FileHandler.h"

void FileHandler::read(const string &outputPath) {

}


void FileHandler::write(const string &outputPath,string str) {
	ofstream out(outputPath);
	if (out.is_open()) {
		out << str;
		out.close();
	}
	
}
