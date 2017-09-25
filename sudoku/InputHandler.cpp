#include "stdafx.h"
#include "InputHandler.h"
#include "FinalMaker.h"
#include "SudokuSolver.h"

void InputHandler::check(int argc, char ** argv){
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "不满足0<n<=1000000！" << endl;
			else {
				FianlMaker fm;
				fm.make(n);
				cout << "已生成" + parameter2 + "个数独终盘" << endl;
			}
		}
		else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << parameter2 + "无法打开！" << endl;
				return;
			}
			char ch[81];
			char c;
			int count = 0;
			SudokuSolver ss;
			FILE* out = fopen("sudoku.txt", "wt");
			while (in.get(c)) {	//in >> c 会忽略空白回车符
				if (isdigit(c)) {
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					fputs(ss.solve(ch),out);
				}
			}
			in.close();
			if (count != 0) {
				char *str = "存在错误格式！";
				fputs(str, out);
				cout << str << endl;
			}
			else
				cout << "已解出" + parameter2 + "里的数独" << endl;
			fclose(out);
		}
		else {
			cout << "输入有误！" << endl;
		}
	}
	else {
		cout << "输入有误！" << endl;
	}
	return;
}

int InputHandler::isNum(const string & s){
	size_t size = s.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(s);
}
