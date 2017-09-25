#include "stdafx.h"
#include "FinalMaker.h"
#include "InputHandler.h"

static char str[163000001];	// (18 * 9 + 1)*1000000+1
static int index = 0;

void FianlMaker::make(int n) {
	num = n;
	count = 0;
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
	while (1) {
		table[0][4] = table[1][1] = table[2][7] = table[3][3] = table[4][0] = table[5][6] = table[6][5] = table[7][2] = table[8][8] = a[0];
		table[0][5] = table[1][2] = table[2][8] = table[3][4] = table[4][1] = table[5][7] = table[6][3] = table[7][0] = table[8][6] = a[1];
		table[0][3] = table[1][0] = table[2][6] = table[3][5] = table[4][2] = table[5][8] = table[6][4] = table[7][1] = table[8][7] = a[2];
		table[0][7] = table[1][4] = table[2][1] = table[3][6] = table[4][3] = table[5][0] = table[6][8] = table[7][5] = table[8][2] = a[3];
		table[0][8] = table[1][5] = table[2][2] = table[3][7] = table[4][4] = table[5][1] = table[6][6] = table[7][3] = table[8][0] = a[4];
		table[0][6] = table[1][3] = table[2][0] = table[3][8] = table[4][5] = table[5][2] = table[6][7] = table[7][4] = table[8][1] = a[5];
		table[0][1] = table[1][7] = table[2][4] = table[3][0] = table[4][6] = table[5][3] = table[6][2] = table[7][8] = table[8][5] = a[6];
		table[0][2] = table[1][8] = table[2][5] = table[3][1] = table[4][7] = table[5][4] = table[6][0] = table[7][6] = table[8][3] = a[7];
		table[0][0] = table[1][6] = table[2][3] = table[3][2] = table[4][8] = table[5][5] = table[6][1] = table[7][7] = table[8][4] = 9;
		memcpy(temp, table, sizeof(table));
		for (int c1 = 0; c1 < 2 ; c1++)
			for (int c2 = 0; c2 < 6 ; c2++)
				for (int c3 = 0; c3 < 6 ; c3++)
					for (int r1 = 0; r1 < 2 ; r1++)
						for (int r2 = 0; r2 < 6 ; r2++)
							for (int r3 = 0; r3 < 6; r3++) {
								combina(c1, c2, c3, r1, r2, r3);
								if (count == num) {
									/*	ofstream out;
									out.open("sudoku.txt", ios::out | ios::trunc);	// 写入前先清空文件
									out << str;
									out.close();*/
									FILE* out=fopen("sudoku.txt", "wt");
									fputs(str, out);
									fclose(out);
									return;
								}
							}
		next_permutation(a, a + 8);	 // 按升序进行全排列一次，只排列前8个元素
	}
}

void FianlMaker::record() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			str[index++] = table[i][j] + '0';
			str[index++] = ' ';
		}
		str[index++] = table[i][8] + '0';
		str[index++] = '\n';
	}
	str[index++] = '\n';
	count++;
}

void FianlMaker::rowExchange(const int& r1, const int& r2) {
	for (int i = 0; i < 9; i++) {
		int t = table[r1][i];
		table[r1][i] = table[r2][i];
		table[r2][i] = t;
	}
}

void FianlMaker::colExchange(const int& c1, const int& c2) {
	for (int i = 0; i < 9; i++) {
		int t = table[i][c1];
		table[i][c1] = table[i][c2];
		table[i][c2] = t;
	}
}

void FianlMaker::combina(const int& c1, const int& c2, const int& c3, const int& r1, const int& r2, const int& r3) {
	memcpy(table, temp, sizeof(temp));
	if (c1 == 1)
		colExchange(1, 2);
	switch (c2) {
	case 1:
		colExchange(4, 5);
		break;
	case 2:
		colExchange(3, 4);
		break;
	case 3:
		colExchange(3, 4);
		colExchange(4, 5);
		break;
	case 4:
		colExchange(3, 5);
		colExchange(4, 5);
		break;
	case 5:
		colExchange(3, 5);
		break;
	}
	switch (c3) {
	case 1:
		colExchange(7, 8);
		break;
	case 2:
		colExchange(6, 7);
		break;
	case 3:
		colExchange(6, 7);
		colExchange(7, 8);
		break;
	case 4:
		colExchange(6, 8);
		colExchange(7, 8);
		break;
	case 5:
		colExchange(6, 8);
		break;
	}
	if (r1 == 1)
		rowExchange(1, 2);
	switch (r2) {
	case 1:
		rowExchange(4, 5);
		break;
	case 2:
		rowExchange(3, 4);
		break;
	case 3:
		rowExchange(3, 4);
		rowExchange(4, 5);
		break;
	case 4:
		rowExchange(3, 5);
		rowExchange(4, 5);
		break;
	case 5:
		rowExchange(3, 5);
		break;
	}
	switch (r3) {
	case 1:
		rowExchange(7, 8);
		break;
	case 2:
		rowExchange(6, 7);
		break;
	case 3:
		rowExchange(6, 7);
		rowExchange(7, 8);
		break;
	case 4:
		rowExchange(6, 8);
		rowExchange(7, 8);
		break;
	case 5:
		rowExchange(6, 8);
		break;
	}
	record();
}
