#pragma once

#include "stdafx.h"

using namespace std;

const int maxrow = 9 * 9 * 9;
const int maxcol = 1 + 9 * 9 * 4;
const int num = maxcol + maxrow * 4;	// 总元素个数,  第一个为Head元素,接着9*9*4个为列标元素,最后9*9*9*4个为“1”元素

class SudokuSolver {
public:
	string solve(char ch[]);

private:
	int Left[num], Right[num], Up[num], Down[num];	// 每个元素的4个方向分量（相当于链表中的箭头）
	int Col[num];		// 记录每元素的列标元素
	int Row[num];		// 记录每个元素所在的01矩阵行数
	int Size[maxcol];	// 记录每列“1”元素数
	int Head[maxrow];	// 记录每行第一个“1”元素
	int table[9][9];	// 数独
	int no;				// 元素编号
	string out;
	void transform(int table[][9], char ch[]);
	void link();
	void insertNode(int c, int cnt);
	void remove(int c);
	void restore(int c);
	bool dfs(int k);
};
