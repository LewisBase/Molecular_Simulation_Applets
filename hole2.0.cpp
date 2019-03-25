// 计算界面上产生的空洞大小
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>

#define PI 3.1415926535898

using namespace std;

struct Atom
{
	string aname;
	double asig;
};

const int k_A = 22;               // 原子种类
const Atom Sig[k_A] = 
{
	{"R1", 0.43},    
	{"R2", 0.43},
    {"R3", 0.43},
    {"DN", 0.47},
    {"R4", 0.43},
    {"R5", 0.43},
    {"RO", 0.43},
    {"C1A", 0.47},
    {"C2A", 0.47},
    {"C3A", 0.47},
    {"R6", 0.47},
    {"R7", 0.47},
    {"R8", 0.47},
    {"NC3", 0.47},
    {"PO4", 0.47},
    {"GL1", 0.47},
    {"GL2", 0.47},
    {"C4A", 0.47},
    {"C1B", 0.47},
    {"C2B", 0.47},
    {"C3B", 0.47},
    {"C4B", 0.47},
};                                 // 粒子直径
const double dL = 0.1;             // 分格增量

double distance(const double &, const double &, const double &, const double &, 
	const string &, const double &, const double &);

int main()
{


	// 批量文件读入与输出
	char input[100];
	for (int file = 0; file < 101; file++)
	{
		string tip;                   // 无效信息
    	int NumA = 0;                 // 界面上总粒子数
    	string atomname[1000];        // 原子名称
    	double lxu, lyu, lzu;         // 盒子大小x, y, z
    	double coor[1000][3];         // 界面上粒子坐标
    	double x,y;                   // 随机点坐标
    	double HR=0;                  // 空穴初始半径
    	double maxHR=0;               // 空穴最大半径
		double minHRD=8;
		double * maxHRD=new double [100000];


		sprintf(input,"md%d.gro",file);
    	ifstream fin(input, ios::in);
    	// 读入原子坐标
		fin >> tip >> tip >> tip >> tip >> tip >> tip >> tip >> tip;    //按实际情况更改
    	fin >> NumA;
		cout << "Total number: " << NumA << endl;
    	fin >> tip;
		cout << "Start Read Atoms' Coordinates:" << endl;
		cout << tip << endl;
    	int a;
    	for (a=0; a < NumA; a++)
    	{
				if (a != (NumA-1))
				{
    	            fin >> atomname[a];    //读入原子种类
    	            cout << atomname[a] << endl;
    	            fin >> tip;
    	        	fin >> coor[a][0] >> coor[a][1] >> coor[a][2];
					cout << coor[a][0] << "\t" << coor[a][1] << endl;
    	            fin >> tip;
				}
				else
				{
					fin >> atomname[a];    //读入原子种类
    	            cout << atomname[a] << endl;
					fin >> tip;
					fin >> coor[a][0] >> coor[a][1] >> coor[a][2];
					cout << coor[a][0] << "\t" << coor[a][1] << endl;
				}
    	}
		cout << "Total atom number is: " << a << endl;
    	fin >> lxu >> lyu >> lzu;
		cout << "Box size: " << lxu << "\t" << lyu << "\t" << lzu << endl;
		fin.close();

		// 计算与分子间距离
		int n;
		n=0;
    	for (x=0.0; x<lxu; x+=dL)
    	{
    	    for (y=0.0; y<lyu; y+=dL)
    	    {
    	        for (int i=0; i<NumA; i++)
    	        {
    	            HR = distance(x, y, coor[i][0], coor[i][1], atomname[i], lxu, lyu);
					if (HR > 0 && minHRD >= HR)
						minHRD = HR;
				}
				maxHRD[n] = minHRD;
				minHRD = 8;
				n++;
    	    }
    	}
		
		ofstream fout("output.dat", ios::out | ios::app);
		//对各个位置上空穴大小排序
		cout << "n: " << n << endl;
		for (int j=0; j<n; j++)
		{
			cout << "maxHRD: " << maxHRD[j] << endl;
			//fout << "maxHRD: " << maxHRD[j] << endl;		
			if (maxHR <= maxHRD[j])
				maxHR = maxHRD[j];
		}
	
	    cout << "The Biggest Radius of Hole is " << maxHR << "nm" << endl;
	    fout << maxHR << endl;
	    
		delete [] maxHRD;
		fout.close();
	}
	    
    return 0;
}

double distance(const double & x1,const double & y1,const double & x2,
    const double & y2,const string & atname, const double & lx, const double & ly)
{
    double dx, dy;                 // x1-x2, y1-y2
    double r;
    double sigm;
    dx = abs(x1-x2);
    dy = abs(y1-y2);
    if (dx > lx/2.0)
        dx = lx - dx;
    if (dy > ly/2.0)
        dy = ly - dy;
    for (int i=0; i<k_A; i++)
    {
        if (Sig[i].aname == atname)
            sigm = Sig[i].asig/2;
    }
    r = sqrt(dx*dx + dy*dy) - sigm;
	cout << "Atom: " << atname << " Sigm: " << sigm 
		<< " X: " << x1 << " Y: " << y1 << " R: " << r << endl;
    return r;
}
