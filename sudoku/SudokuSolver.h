#pragma once

#include "stdafx.h"

using namespace std;

const int maxrow = 9 * 9 * 9;
const int maxcol = 1 + 9 * 9 * 4;
const int num = maxcol + maxrow * 4;	// 总元素个数,  第一个为Head元素,接着9*9*4个为列标元素,最后9*9*9*4个为“1”元素

class SudokuSolver {
public:
	char* solve(char ch[]);

private:
	int table[9][9];	// 数独
	int no;				// 元素编号
	void transform(int table[][9], char ch[]);
	void link();
	void insertNode(int col, int no);
	void remove(int col);
	void restore(int col);
	bool dfs(int k);
};
