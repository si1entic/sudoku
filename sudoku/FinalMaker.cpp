#include "stdafx.h"
#include "FinalMaker.h"


string FianlMaker::make(int n){
	num = n;
	count = 0;
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
	while (count < num) {
		makeTable(a);
		next_permutation(a, a + 8);	 // 按升序进行全排列一次，只排列前8个元素
	}
	return str;
}

bool FianlMaker::tableToString(int table[][9]){
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			str += char(table[i][j] + '0');
			if (j != 8) {
				str += " ";
			}
		}
		str += "\n";
	}
	str += "\n";
	count++;
	return count < num ? true : false;
}

void FianlMaker::rowExchange(int table[][9], int r1, int r2){
	int temp; 
	for (size_t i = 0; i < 9; i++){
		temp = table[r1][i];
		table[r1][i] = table[r2][i];
		table[r2][i] = temp;
	}
}

void FianlMaker::colExchange(int table[][9], int c1, int c2){
	for (size_t i = 0; i < 9; i++) {
		int temp;
		temp = table[i][c1];
		table[i][c1] = table[i][c2];
		table[i][c2] = temp;
	}
}

void FianlMaker::combina(int c1, int c2, int c3, int r1, int r2, int r3){
	int t[9][9];
	memcpy(t, table, sizeof(table));
	if (c1 == 1)
		colExchange(t, 1, 2);

	if(c2==1)
		colExchange(t, 4, 5);
	else if (c2 == 2)
		colExchange(t, 3, 4);
	else if (c2 == 3) {
		colExchange(t, 3, 4);
		colExchange(t, 4, 5);
	}
	else if (c2 == 4) {
		colExchange(t, 3, 5);
		colExchange(t, 4, 5);
	}
	else if (c2 == 5) 
		colExchange(t, 3, 5);

	if (c3 == 1)
		colExchange(t, 7, 8);
	else if (c3 == 2)
		colExchange(t, 6, 7);
	else if (c3 == 3) {
		colExchange(t, 6, 7);
		colExchange(t, 7, 8);
	}
	else if (c3 == 4) {
		colExchange(t, 6, 8);
		colExchange(t, 7, 8);
	}
	else if (c3 == 5)
		colExchange(t, 6, 8);

	if (r1 == 1)
		rowExchange(t, 1, 2);

	if (r2 == 1)
		rowExchange(t, 4, 5);
	else if (r2 == 2)
		rowExchange(t, 3, 4);
	else if (r2 == 3) {
		rowExchange(t, 3, 4);
		rowExchange(t, 4, 5);
	}
	else if (r2 == 4) {
		rowExchange(t, 3, 5);
		rowExchange(t, 4, 5);
	}
	else if (r2 == 5)
		rowExchange(t, 3, 5);

	if (r3 == 1)
		rowExchange(t, 7, 8);
	else if (r3 == 2)
		rowExchange(t, 6, 7);
	else if (r3 == 3) {
		rowExchange(t, 6, 7);
		rowExchange(t, 7, 8);
	}
	else if (r3 == 4) {
		rowExchange(t, 6, 8);
		rowExchange(t, 7, 8);
	}
	else if (r3 == 5)
		rowExchange(t, 6, 8);

	tableToString(t);
}

void FianlMaker::makeTable(int a[]) {
	table[0][4] = table[1][1] = table[2][7] = table[3][3] = table[4][0] = table[5][6] = table[6][5] = table[7][2] = table[8][8] = a[0];
	table[0][5] = table[1][2] = table[2][8] = table[3][4] = table[4][1] = table[5][7] = table[6][3] = table[7][0] = table[8][6] = a[1];
	table[0][3] = table[1][0] = table[2][6] = table[3][5] = table[4][2] = table[5][8] = table[6][4] = table[7][1] = table[8][7] = a[2];
	table[0][7] = table[1][4] = table[2][1] = table[3][6] = table[4][3] = table[5][0] = table[6][8] = table[7][5] = table[8][2] = a[3];
	table[0][8] = table[1][5] = table[2][2] = table[3][7] = table[4][4] = table[5][1] = table[6][6] = table[7][3] = table[8][0] = a[4];
	table[0][6] = table[1][3] = table[2][0] = table[3][8] = table[4][5] = table[5][2] = table[6][7] = table[7][4] = table[8][1] = a[5];
	table[0][1] = table[1][7] = table[2][4] = table[3][0] = table[4][6] = table[5][3] = table[6][2] = table[7][8] = table[8][5] = a[6];
	table[0][2] = table[1][8] = table[2][5] = table[3][1] = table[4][7] = table[5][4] = table[6][0] = table[7][6] = table[8][3] = a[7];
	table[0][0] = table[1][6] = table[2][3] = table[3][2] = table[4][8] = table[5][5] = table[6][1] = table[7][7] = table[8][4] = a[8];
	for (size_t c1 = 0; c1 < 2 && count<num; c1++)
		for (size_t c2 = 0; c2 < 6 && count<num; c2++)
			for (size_t c3 = 0; c3 < 6 && count<num; c3++)
				for (size_t r1 = 0; r1 < 2 && count<num; r1++)
					for (size_t r2 = 0; r2 < 6 && count<num; r2++)
						for (size_t r3 = 0; r3 < 6 && count<num; r3++)
							combina(c1, c2, c3, r1, r2, r3);
}
