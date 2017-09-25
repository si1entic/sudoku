#include "stdafx.h"
#include "SudokuSolver.h"

int Left[num], Right[num], Up[num], Down[num];	// 每个元素的4个方向分量（相当于链表中的箭头）
int Col[num];		// 记录每个元素的列标元素
int Row[num];		// 记录每个元素所在的01矩阵行数
int Size[maxcol];	// 记录每列的“1”元素个数
int Head[maxrow];	// 记录每行第一个“1”元素
static char str[163];
static int index;

char* SudokuSolver::solve(char ch[]) {
	index = 0;
	transform(table, ch);
	link();
	int select = 0;
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int k = table[i][j];
			if (k) {	// 代表数独题目已给数字的行必选
				int row = i * 81 + j * 9 + k - 1;
				select++;
				remove(Col[Head[row]]);		// 移除该行首元素及其相关元素
				for (int u = Right[Head[row]]; u != Head[row]; u = Right[u])	// 移除该行其他元素及其相关元素
					remove(Col[u]);
			}
		}
	}

	(dfs(select + 1));

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 8; j++) {
			str[index++] = char(table[i][j] + '0');
			str[index++] = ' ';
		}
		str[index++] = (table[i][8] + '0');
		str[index++] = '\n';
	}
	str[index++] = '\n';
	return str;
}

void SudokuSolver::transform(int table[][9], char ch[]) {
	int index = 0;
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			table[i][j] = ch[index++] - '0';
	return;
}

void SudokuSolver::link() {
	/* 链接列标元素 */
	for (size_t i = 0; i < maxcol; i++) {
		Left[i] = i - 1;
		Right[i] = i + 1;
		Up[i] = Down[i] = i;
		Row[i] = 0;
		Col[i] = i;
		Size[i] = 0;
	}
	/* 链接Head元素 */
	Left[0] = maxcol - 1;
	Right[maxcol - 1] = 0;
	no = maxcol;
	/* 链接“1”元素 */
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {	// 遍历9x9数独
			int k = table[i][j];
			if (k) {
				for (size_t t = 1; t <= 4; t++) {	// 每个非0数字会在01矩阵中产生4个“1”元素
					Left[no + t] = no + t - 1;
					Right[no + t] = no + t + 1;
					Row[no + t] = i * 81 + j * 9 + k - 1;
				}
				Left[no + 1] = no + 4;
				Right[no + 4] = no + 1;
				Head[Row[no + 1]] = no + 1;
				/* 将4个元素插入列链中 */
				insertNode(i * 9 + j + 1, no + 1);
				insertNode(81 + i * 9 + k, no + 2);
				insertNode(81 * 2 + j * 9 + k, no + 3);
				insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
				no += 4;
			}
			else {	// 该位置为0，即待填
				for (size_t k = 1; k <= 9; k++) {	// 构造9种填法
					for (size_t t = 1; t <= 4; t++) {	// 生成并链接它们的元素
						Left[no + t] = no + t - 1;
						Right[no + t] = no + t + 1;
						Row[no + t] = i * 81 + j * 9 + k - 1;
					}
					Left[no + 1] = no + 4;
					Right[no + 4] = no + 1;
					Head[Row[no + 1]] = no + 1;
					insertNode(i * 9 + j + 1, no + 1);
					insertNode(81 + i * 9 + k, no + 2);
					insertNode(81 * 2 + j * 9 + k, no + 3);
					insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
					no += 4;
				}
			}
		}
	}
}

void SudokuSolver::insertNode(int col, int no) {	// 将no号元素添加到col列里
	/* 在元素col和Down[col]之间插入no */
	Up[Down[col]] = no;
	Down[no] = Down[col];
	Up[no] = col;
	Down[col] = no;
	Size[col]++;
	Col[no] = col;
}

void SudokuSolver::remove(int col) {	// 按列标元素移除相关元素
	/* 移除col列标元素 */
	Left[Right[col]] = Left[col];
	Right[Left[col]] = Right[col];
	/* 移除col列“1”元素与其同行元素 */
	for (size_t i = Down[col]; i != col; i = Down[i]) {	// 向下删
		for (size_t j = Right[i]; j != i; j = Right[j]) {	// 向右删
			Up[Down[j]] = Up[j];
			Down[Up[j]] = Down[j];
			Size[Col[j]]--;
		}
	}
}

void SudokuSolver::restore(int col) {
	/* 恢复col列标元素 */
	Left[Right[col]] = Right[Left[col]] = col;
	/* 恢复col列“1”元素与其同行元素 */
	for (size_t i = Up[col]; i != col; i = Up[i]) {		// 恢复顺序与移除顺序相反
		for (size_t j = Left[i]; j != i; j = Left[j]) {
			Up[Down[j]] = Down[Up[j]] = j;
			Size[Col[j]]++;
		}
	}
}

bool SudokuSolver::dfs(int select) {
	if (select > 81)	// 已选够
		return true;
	/* 遍历列标元素，选一个元素最少的列（回溯率低） */
	int col = 0;
	int min = INT_MAX;
	for (size_t i = Right[0]; i!=0; i=Right[i])	{
		int size = Size[i];
		if (size == 0)
			return false;
		if (size < min) {
			min = size;
			col = i;
		}
	}
	remove(col);
	/* 遍历该列各“1”元素,逐行依次尝试,失败则恢复已移除的结点 */
	for (size_t i = Down[col]; i !=col; i=Down[i]) {
		int row = Row[i];
		table[row / 81][row % 81 / 9] = row % 9 + 1;	// 根据该元素的行填入数独
		for (size_t j = Right[i]; j != i; j = Right[j])	// 移除与该元素同行元素的列 
			remove(Col[j]);
		if (dfs(select + 1))	// 已选行数+1，递归
			return true;
		for (size_t j = Left[i]; j != i; j = Left[j])	// 返回false则恢复刚才的移除，顺序相反
			restore(Col[j]);
	}
	restore(col);
	return false;
}






