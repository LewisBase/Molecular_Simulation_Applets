//读取初始输入文件中的坐标，生成移动后新的坐标
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>   // for exit()
#include<vector>
#include<string>
#include<cctype>

const char * file = "input.dat";

int main()
{
    using namespace std;
    ifstream fin; 
	ofstream fout;// read and write streams
    fin.open(file);
    if (!fin.is_open())
    {
        cerr << file << " could not be opened.\n";
        exit(EXIT_FAILURE);
    }
	
	double vec[12][4];
	double increasement;
	int n=0;
	string null;

	//cout << "Input the increasement of z axis.\n";
	cin >> increasement;

	for (int i = 0; i < 134; i++)	//读入无效行
	{	
		fin >> null;
		//cout << null << endl;
	}
	//cout << "END" << endl;

	//cout << "Read coordinate" << endl;		
	for (int i = 0; i < 12; i++)	//读入z轴坐标
	{	
		for (int j = 0; j < 4; j++)
		{					
			fin >> vec[i][j];
	//		cout << vec[i][j] << endl;
		}
	}

	//for (int i = 0; i < 12; i++)
	//{
	//	for (int j = 0; j < 4; j++)		
	//		cout << "Before fix" << vec[i][j] << endl;
	//}
	for (int i = 0; i < 12; i++)	//修改z轴坐标
		vec[i][3] += increasement;
	//for (int i = 0; i < 12; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//		cout << "After fix " << vec[i][j] << endl;
	//}
	fin.close();

	fout.open("new.dat", ios::app);
	for (int i = 0; i < 12; i++)	//写出新的z轴坐标
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
