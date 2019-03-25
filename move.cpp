//移动坐标，更新了可读入文件与无效信息读入的方法
//更新中心点的坐标为质心坐标
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cctype>
#include<cstdlib>


const double center[3] = {15.0, 15.0, 18.0};
/*
atomnumber为平移体系中的总原子数
centeratom为平移过程中的中心原子序号
center[3]为中心原子平移后的坐标
*/

using namespace std;

int main()
{
    string filename, outfilename;
    cout << "Input the filename(without -z.pdb): " << endl;
    cin >> filename;
    filename += "-z.pdb";
    int atomnumber;
    //int centeratom;
    cout << "Input the total atom number:"
        << endl << "atomnumber= " << endl;
    cin >> atomnumber;
    //cout << "centeratom= " << endl;
    //cin >> centeratom;
	
    ifstream fin;
	ofstream fout;
    outfilename = "out-"+filename;
	fin.open(filename.c_str(),ios::in);
	if (!fin.is_open())
	{
		cerr << filename << " could not be opened.\n";
		exit(EXIT_FAILURE);	
	}

	double vec[atomnumber][5];      // 0-序号，1-x，2-y，3-z，4-质量
    double masscenter[3]={0.0,0.0,0.0}; // 质心坐标
    double totalmass=0.0;           // 总质量
	double move[3]={0.0,0.0,0.0};   // 移动向量
	string atomname[atomnumber];    // 原子名称
	string null;

	//读入坐标信息
    cout << endl << "Information: " << endl;
    while (fin >> null)
    {
        cout << null << "\t";
        if (null == "1")
            break;
    }
    fin >> null;
    cout << null << endl;
	for (int i = 0; i < atomnumber; i++)
	{
		fin >> null;
		fin >> vec[i][0];
		fin >> atomname[i];
		fin >> null >> null >> null;					
		fin >> vec[i][1] >> vec[i][2] >> vec[i][3];
		fin >> null >> null >> null; 
	}
    for (int i = 0; i < atomnumber; i++)
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
    if (totalmass != 0)
    {
        for (int i = 0; i < 3; i++)
            masscenter[i] /= totalmass;
    }
	for (int i = 0; i < atomnumber; i++)
	{
		cout.width(4);		
		cout << left << atomname[i] << " " << vec[i][0] << " " << vec[i][1] 
			<< " " << vec[i][2] << " " << vec[i][3] << " " << vec[i][4] << endl;
	}
    cout << "Total mass: " << totalmass << " " << "Masscenter: " << masscenter[0] << " " << masscenter[1] << " " << masscenter[2] << endl;
	fin.close();

	//计算移动差值
	for (int j = 0; j < 3; j++)
	{
		move[j] = masscenter[j] - center[j];
	}
	for (int i = 0; i < atomnumber; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vec[i][j+1] -= move[j];
		}
	}
	for (int i = 0; i < atomnumber; i++)
	{
		cout.width(4);		
		cout << left << atomname[i] << " " << vec[i][0] << " " << vec[i][1] 
			<< " " << vec[i][2] << " " << vec[i][3] << endl;
	}

	//输出新坐标
	fout.open(outfilename.c_str(),ios::out);
	for (int i = 0; i < atomnumber; i++)
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
				fout << right << fixed << setprecision(1) 
					<< vec[i][j] << " ";
			}
		}
		fout << endl;
	}
	fout.close();
	return 0;
}
