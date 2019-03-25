// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// 计算界面上产生的不规则空洞大小
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>

using namespace std;

struct Atom
{
	string aname;
	double asig;
};

const int k_A = 22;               // 原子种类
const Atom Sig[k_A] =
{
	{ "R1", 0.43 },
	{ "R2", 0.43 },
	{ "R3", 0.43 },
	{ "DN", 0.47 },
	{ "R4", 0.43 },
	{ "R5", 0.43 },
	{ "RO", 0.43 },
	{ "C1A", 0.47 },
	{ "C2A", 0.47 },
	{ "C3A", 0.47 },
	{ "R6", 0.47 },
	{ "R7", 0.47 },
	{ "R8", 0.47 },
	{ "NC3", 0.47 },
	{ "PO4", 0.47 },
	{ "GL1", 0.47 },
	{ "GL2", 0.47 },
	{ "C4A", 0.47 },
	{ "C1B", 0.47 },
	{ "C2B", 0.47 },
	{ "C3B", 0.47 },
	{ "C4B", 0.47 },
};                                 // 粒子直径 单位nm

double distance(const int &, const int &, const double &, const double &,
	const string &, const int &, const int &);
int exploration(const int & mx, const int & my, int map[][100], const int & l);

int main()
{


	// 批量文件读入与输出
	char input[100];
	for (int file = 0; file < 1; file++)
	{
		string tip;                   // 无效信息
		int NumA = 0;                 // 界面上总粒子数
		string atomname[1000];        // 原子名称
		double lxu, lyu, lzu;         // 盒子大小x, y, z 单位nm
		double coor[1000][3];         // 界面上粒子坐标 单位nm
		int x, y;                     // 随机点坐标 单位A
		double HR;					  // 点与原子间距离

		int initialMatrix[100][100];// 初始距阵判断
		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 100; y++)
				initialMatrix[x][y] = 0;
		}


		sprintf_s(input, "md%d.gro", file);
		ifstream fin(input, ios::in);
		// 读入原子坐标
		fin >> tip >> tip >> tip >> tip >> tip >> tip >> tip >> tip;    //按实际情况更改
		fin >> NumA;
		cout << "Total number: " << NumA << endl;
		cout << "Start Read Atoms' Coordinates:" << endl;
		//cout << tip << endl;
		int a;
		for (a = 0; a < NumA; a++)
		{
			fin >> tip;
			fin >> atomname[a];    //读入原子种类
			cout << atomname[a] << endl;
			fin >> tip;
			fin >> coor[a][0] >> coor[a][1] >> coor[a][2];
			coor[a][0] *= 10;	 // 转化单位为A
			coor[a][1] *= 10;
			coor[a][2] *= 10;
			cout << coor[a][0] << "\t" << coor[a][1] << endl;
		}
		cout << "Total atom number is: " << a << endl;
		fin >> lxu >> lyu >> lzu;
		lxu = int(lxu * 10);	 // 转化单位为A
		lyu = int(lyu * 10);
		lzu = int(lzu * 10);
		cout << "Box size: " << lxu << "\t" << lyu << "\t" << lzu << endl;
		fin.close();


		// 判断初始距阵分布
		for (x = 0; x<lxu; x++)
		{
			for (y = 0; y<lyu; y++)
			{
				for (int a = 0; a < NumA; a++)
				{
					HR = distance(x, y, coor[a][0], coor[a][1], atomname[a], lxu, lyu);
					if (HR <= 0)
					{
						initialMatrix[x][y] = 1;
						break;
					}
				}
			}
		}
		int n = 0;
		for (x = 0; x<lxu; x++)
		{
			for (y = 0; y<lyu; y++)
			{
				cout << initialMatrix[x][y] << " ";
				n++;
				if (n % 100 == 0)
					cout << endl;
			}
		}

		// 不规则面积求算
		int num = 0;								// 记录空格点的个数
		int maxarea = 0;
		for (x = 0; x < lxu; x++)
		{
			for (y = 0; y < lyu; y++)
			{
				if (initialMatrix[x][y] == 0)
				{
					num += exploration(x, y, initialMatrix, 100);
					cout << "Area of the Hole: " << num << "A^2" << endl;
					if (maxarea <= num)
						maxarea = num;
					num = 0;
				}
			}
		}
		ofstream fout("area-output.dat", ios::out | ios::app);
		cout << "The Biggest Area of Hole is " << maxarea << "A^2" << endl;
		fout << maxarea << endl;

		fout.close();
	}
	string tip;
	cin >> tip;
	return 0;
}

double distance(const int & x1, const int & y1, const double & x2,
	const double & y2, const string & atname, const int & lx, const int & ly)
{
	double dx, dy;                 // x1-x2, y1-y2
	double r;
	double sigm;
	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	if (dx > lx / 2.0)
		dx = lx - dx;
	if (dy > ly / 2.0)
		dy = ly - dy;
	for (int i = 0; i<k_A; i++)
	{
		if (Sig[i].aname == atname)
			sigm = Sig[i].asig * 5;
	}
	r = sqrt(dx*dx + dy*dy) - sigm;
	cout << "Atom: " << atname << " Radiu: " << sigm << "A" 
		<< " X: " << x1 << " Y: " << y1 << " R: " << r  << "A" << endl;
	return r;
}

int exploration(const int & mx, const int & my, int map[][100], const int & l)
{
	int hole = 0;
	if (map[mx][my] == 0)
	{
		hole++;
		map[mx][my] = -1;
		int right, left, up, down;
		right = mx + 1;
		left = mx - 1;
		up = my + 1;
		down = my - 1;
		if (mx == 99)
		{
			right = 0;
		}
		if (mx==0)
		{
			left = 99;
		}
		if (my==99)
		{
			up = 0;
		}
		if (my==0)
		{
			down = 99;
		}
		hole += exploration(right, my, map, l);
		hole += exploration(left, my, map, l);
		hole += exploration(mx, up, map, l);
		hole += exploration(mx, down, map, l);
		return hole;
	}
	else
		return 0;
}
