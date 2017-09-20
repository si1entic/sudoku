#include "stdafx.h"
#include "InputHandler.h"
#include "FinalMaker.h"

int InputHandler::check(int argc, char ** argv)
{
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "不满足0<n<=1000000！" << endl;
			else {
				string str;
				FianlMaker fm;
				str = fm.make(n);
				ofstream out("sudoku.txt", ios::out | ios::trunc);	// 写入前先清空文件
				if (out.is_open()) {
					out << str;
					out.close();
				}
				cout << "已生成" + parameter2 + "个数独终盘" << endl;
			}
			
		}
		else if (parameter1 == "-s") {
			if (isPath(parameter2)) {
				// 在这调用求解函数
				cout << "已解出" + parameter2 + "里的数独" << endl;
			}
			else
				cout << parameter2 + "不存在！" << endl;
		}
		else {
			cout << "输入有误！" << endl;
		}
	}
	else {
		cout << "输入有误！" << endl;
	}
	return 0;
}

int InputHandler::isNum(const string & str)
{
	size_t size = str.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++){
		int ascii = int(str[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(str);
}

int InputHandler::isPath(const string & str)
{
	fstream file;
	file.open(str, ios::in);
	if (file)
		return 1;
	else {
		return 0;
	}
}