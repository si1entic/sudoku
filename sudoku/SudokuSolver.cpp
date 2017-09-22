#include "stdafx.h"
#include "SudokuSolver.h"

string SudokuSolver::solve(char ch[]) {
	transform(table,ch);
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
	if (dfs(select + 1)) {
		out = "";
		for (size_t i = 0; i < 9; i++) {
			for (size_t j = 0; j < 8; j++)
				out += (to_string(table[i][j]) + " ");
			out += (to_string(table[i][8]) + "\n");
		}
	}
	else
		out = "该数独无解\n";
	out += "\n";
	return out;
}

void SudokuSolver::transform(int table[][9],char ch[]) {
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

void SudokuSolver::insertNode(int c, int no){	// 将no号元素添加到c列里
	/* 在元素c和Down[c]之间插入no */
	Up[Down[c]] = no;
	Down[no] = Down[c];
	Up[no] = c;
	Down[c] = no;
	Size[c]++;
	Col[no] = c;
}

void SudokuSolver::remove(int c){	// 按列标元素移除相关元素
	Left[Right[c]] = Left[c];
	Right[Left[c]] = Right[c];
	for (size_t i = Down[c]; i != c; i = Down[i]) {	// 向下删
		for (size_t j = Right[i]; j != i; j = Right[j]) {	// 向右删
			Up[Down[j]] = Up[j];
			Down[Up[j]] = Down[j];
			Size[Col[j]]--;
		}
	}
}

void SudokuSolver::restore(int c){	
	/* 恢复c列标元素 */
	Left[Right[c]] = Right[Left[c]] = c;
	/* 恢复c列“1”元素与其同行元素 */
	for (size_t i = Up[c]; i != c; i = Up[i]){		// 恢复顺序与移除顺序相反
		for (size_t j = Left[i]; j != i; j = Left[j]){	 
			Up[Down[j]] = Down[Up[j]] = j;
			Size[Col[j]]++;
		}
	}
}

bool SudokuSolver::dfs(int select){
	if (select > 81)	// 已选够
		return true;
	int c, minnum = INT_MAX;
	/* 遍历列标元素，选一个元素最少的列（回溯率低） */
	for (size_t i = Right[0]; i != 0; i = Right[i]) {	
		if (Size[i] == 0)
			return false;
		if (Size[i] < minnum){
			minnum = Size[i];
			c = i;
		}
	}
	remove(c);
	/* 遍历该列各“1”元素 */
	for (int i = Down[c]; i != c; i = Down[i]){
		int row = Row[i];
		table[row / 81][row % 81 / 9] = row % 9 + 1;	// 根据该元素的行填入数独
		for (size_t j = Right[i]; j != i; j = Right[j])	// 移除与该元素同行元素的列
			remove(Col[j]);
		if (dfs(select + 1))	// 已选行数+1，递归调用
			return true;
		for (size_t j = Left[i]; j != i; j = Left[j])	// 递归返回false，说明后续无法满足，故恢复与该元素同行元素的列，循坏进入本列下一元素
			restore(Col[j]);
	}
	restore(c);
	return false;
}






