//读取初始输入文件中的坐标，计算质心坐标
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
	string file2;
	cout << "Input the PDB filename and atomnumber: " << endl;
	cin >> file2 >> atomnumber;
    file2 += "-z.pdb";
    ifstream fin1;
	ofstream fout;// read and write streams
    fin1.open(file1);
    if (!fin1.is_open())
    {
        cerr << file1 << " could not be opened.\n";
        exit(EXIT_FAILURE);
    }
	
	double vec[atomnumber][5];
	double totalmass=0.0;
	double masscenter[3]={0.0,0.0,0.0};
	string atomname[atomnumber];
	string null;


	while (fin1 >> null)
    {
        if (null == "z")
            break;
    }
    //cout << null << endl;	
    for (int i = 0; i < atomnumber; i++)	//读入z轴坐标 此处的i对应界面上分子的原子个数
	{	
		for (int j = 0; j < 4; j++)
		{					
			fin1 >> vec[i][j];
		}
	}
	fin1.close();
	
	ifstream fin2;
	fin2.open(file2.c_str());
	if (!fin2.is_open())
    {
        cerr << file2 << " could not be opened.\n";
        exit(EXIT_FAILURE);
    }
    while (fin2 >> null)
    {
        //cout << null << "\t";
        if (null == "1")
            break;
    }
    fin2 >> null;
    //cout << null << endl;
	for (int i = 0; i < atomnumber; i++)	//读入原子名称
	{
		fin2 >> null >> null;
		fin2 >> atomname[i];
		fin2 >> null >> null >> null;					
		fin2 >> null >> null >> null;
		fin2 >> null >> null >> null; 
	}
	fin2.close();

	for (int i = 0; i < atomnumber; i++)	//计算质量与质心坐标
    {
        if (atomname[i] == "C")
            vec[i][4] = 12;
        else if (atomname[i] == "N")
            vec[i][4] = 14;
        else if (atomname[i] == "O")
            vec[i][4] = 16;
        else if (atomname[i] == "H")
            vec[i][4] = 1;
        else if (atomname[i] == "S")
            vec[i][4] = 32;
        else if (atomname[i] == "Cl")
            vec[i][4] = 35.5;
        else if (atomname[i] == "P")
            vec[i][4] = 31;
        else if (atomname[i] == "Br")
            vec[i][4] = 79.9;
        masscenter[0] += vec[i][1] * vec[i][4];
        masscenter[1] += vec[i][2] * vec[i][4];
        masscenter[2] += vec[i][3] * vec[i][4];
        totalmass += vec[i][4];
    }
    
    /*for (int i = 0; i < atomnumber; i++)
    {
        cout << vec[i][0] << "\t" << atomname[i] << "\t" << vec[i][4] << "\t" << 
                vec[i][1] << "\t" <<  vec[i][2] << "\t" << vec[i][3] << endl;
    }*/

	if (totalmass != 0)
    {
        for (int i = 0; i < 3; i++)
            masscenter[i] /= totalmass;
    }
	cout << "masscenter: " << masscenter[0] << "\t" << masscenter[1] << "\t" << masscenter[2] << endl;
	return 0;
}
