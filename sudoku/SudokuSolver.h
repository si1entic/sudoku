#pragma once

#include "stdafx.h"

using namespace std;

class SudokuSolver {
public:
	string solve(char ch[]);

private:
	int table[9][9];	// Êý¶À
	int no;				// ÔªËØ±àºÅ
	string out;
	void transform(int table[][9], char ch[]);
	void link();
	void insertNode(int col, int no);
	void remove(int col);
	void restore(int col);
	bool dfs(int k);
};
