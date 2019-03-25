//读取初始输入文件中的坐标，生成旋转后新的坐标
//改进了读入无效行的方法，不再需要无效行行号
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>   // for exit()
#include<vector>
#include<string>
#include<cctype>
#include<cmath>

#define PI 3.1415926535898
const char * file1 = "input.dat";

int main()
{
    using namespace std;
    int atomnumber;
	string file;
	cin >> atomnumber >> file;
	double vec[atomnumber][4];
	int n=0;
	string null;


    ifstream fin1;
	ofstream fout;// read and write streams
    fin1.open(file1);
    if (!fin1.is_open())
    {
        cerr << file1 << " could not be opened.\n";
        exit(EXIT_FAILURE);
    }
	while (fin1 >> null)
    {
        if (null == "z")
            break;
    }
    for (int i = 0; i < atomnumber; i++)	//读入z轴坐标 此处的i对应界面上分子的原子个数
	{	
		for (int j = 0; j < 4; j++)
		{					
			fin1 >> vec[i][j];
		}
	}
	fin1.close();
	
	if (file == "x-7")
	{
		for (int i = 0; i < atomnumber; i++)	//进行移动，修改坐标
		{
			vec[i][0] = vec[i][0];
			vec[i][1] = vec[i][1]-8.0;
			vec[i][2] = vec[i][2];
			vec[i][3] = vec[i][3]+5.0;
    	}
	}else if (file == "x-23")
	{
		for (int i = 0; i < atomnumber; i++)	//进行移动，修改坐标
		{
			vec[i][0] = vec[i][0];
			vec[i][1] = vec[i][1]+8.0;
			vec[i][2] = vec[i][2];
			vec[i][3] = vec[i][3]-5.0;
    	}
	}else
	{
		cout << "ERROR!Wrong filename!";
	}

	fout.open("new.dat", ios::app);
	for (int i = 0; i < atomnumber; i++)	//写出新的z轴坐标
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				fout.width(2);
				fout << left << int(vec[i][j]) << " ";
			}
			else
			{			
				fout.width(4);
				fout.setf(ios::fixed);
				fout << right << fixed << setprecision(1) << vec[i][j] << " ";
			}
			n++;
			if (n%4 == 0)
				fout << endl;
		}
	}
	fout.close();
	return 0;	
}
