#pragma once

#include "stdafx.h"

using namespace std;

class FianlMaker {
public:
	string make(int n);

private:
	int num,count;
	int table[9][9];
	string str;
	bool tableToString(int table[][9]);
	void rowExchange(int table[][9],int r1, int r2);
	void colExchange(int table[][9],int c1, int c2);
	void combina(int c1, int c2, int c3, int r1, int r2, int r3);
	void makeTable(int a[]);
};
