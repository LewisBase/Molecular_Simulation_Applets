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
	int n=0;
	string null;


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
    cout << null << endl;
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

    for (int i = 0; i < atomnumber; i++)
    {
        cout << vec[i][0] << atomname[i] << "\t" << vec[i][4] << "\t"
            << vec[i][1] << "\t" << vec[i][2] << "\t" << vec[i][3] << endl;
    }

	if (totalmass != 0)
    {
        for (int i = 0; i < 3; i++)
            masscenter[i] /= totalmass;
    }

	double rotateangle;
	double newcenter[3]={0.0,0.0,0.0};		//直接旋转后的质心
	double vecr[atomnumber][4];
	cout << "Input the rotateangle of rotation.\n";
	cin >> rotateangle;
	rotateangle = rotateangle*PI/180.0;
	
	// rotate y
	newcenter[0]=masscenter[0]*cos(rotateangle)+masscenter[2]*sin(rotateangle);
	newcenter[1]=masscenter[1];
	newcenter[2]=masscenter[2]*cos(rotateangle)-masscenter[0]*sin(rotateangle);

	for (int i = 0; i < atomnumber; i++)	//进行旋转，修改坐标
	{
		vecr[i][0] = vec[i][0];
		vecr[i][1] = vec[i][1]*cos(rotateangle)+vec[i][3]*sin(rotateangle)+(masscenter[0]-newcenter[0]);
		vecr[i][2] = vec[i][2]+(masscenter[1]-newcenter[1]);
		vecr[i][3] = vec[i][3]*cos(rotateangle)-vec[i][1]*sin(rotateangle)+(masscenter[2]-newcenter[2]);
    }

	fout.open("new.dat", ios::app);
	for (int i = 0; i < atomnumber; i++)	//写出新的z轴坐标
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				fout.width(2);
				fout << left << int(vecr[i][j]) << " ";
			}
			else
			{			
				fout.width(4);
				fout.setf(ios::fixed);
				fout << right << fixed << setprecision(1) << vecr[i][j] << " ";
			}
			n++;
			if (n%4 == 0)
				fout << endl;
		}
	}
	fout.close();
	return 0;	
}
