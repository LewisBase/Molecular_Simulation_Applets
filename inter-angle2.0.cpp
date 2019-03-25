#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<cctype>

using namespace std;
const double PI=3.1415926535898;
const int ROWIN=2000;                 //输入总行数
//const int ROWOUT=100;                 //输出总行数

int main()
{
	// input message
    int COL=0;                        //角度数据列数
    cout << "Input the number of column: " << endl;
    cin >> COL;
	double * sita = new double [2000];//输入sita角度
	double * fai = new double [2000]; //输出fai角度
	double ** cor = new double *[COL];//二维数组中行与列与实际情况中的相反
    for (int a=0; a<COL; a++)
        cor[a] = new double [2000];   //存放输入数据
	string tip;                       //无用信息
	int R = 0;                        //行数统计

	//output message
	double * sitaout = new double [2000]; //输出sita角度
	double ** corout = new double *[2000];//存放输出信息
    for (int a=0; a<COL; a++)
        corout[a] = new double [2000];

	//normalizing
	double cf[COL];                       //积分值

	//read-in
	ifstream fin;
	fin.open("Angles.dat",ios::in);
	if (!fin.is_open())
	{
		cerr << "Could not open the file!" << endl;
		exit(EXIT_FAILURE);
	}
	fin >> tip >> tip;
    for (int a=0; a<COL; a++)
        fin >> tip;
	cout << "Read in file data!" << endl << "sita fai 0 1 2 3 4..." << endl;
	for (int i=0; i<ROWIN; i++)
	{
		fin >> sita[i] >> fai[i];
        for (int a=0; a<COL; a++)
            fin >> cor[a][i];
		if (fai[i]>(PI/2)&&fai[i]<(3*PI/2))
        {
            sita[i] = -1*sita[i];
        }
		cout.width(4);
		cout << right << sita[i] << "\t" << fai[i] << "\t";
        for (int a=0; a<COL; a++)
            cout << cor[a][i] << "\t";
        cout << endl;
	}
	fin.close();

	/*//test
	double cf11=0,cf21=0,cf31=0;
	for (int k=0; k<ROWIN; k++)
	{
		cf11 += cor[0][k];
		cf21 += cor[1][k];
		cf31 += cor[2][k];
	}
	cout << "cf11=" << cf11 << endl << "cf21=" << cf21 << endl << "cf31=" << cf31 << endl;
    */

	//intergrate
	for (int j=0; j<(ROWIN-1); j++)
	{
        if (sita[j] == sita[j+1])
		{
			//cout << "sita[" << j << "]=sita[" << j+1 << "]=" << sita[j] << endl;
			for (int a=0; a<COL;a++)
            {
                cor[a][j+1] += cor[a][j];
            }
		}
		else
		{
			sitaout[R] = sita[j];
            for (int a=0; a<COL; a++)
            {
                corout[a][R] = cor[a][j];
            }
			R++;
		}
	}
	cout << "R=" << R << endl;
	sitaout[R] = sita[1999];
    for (int a=0; a<COL; a++)
    {
        corout[a][R] += cor[a][1999];
    }

	// normalize
    for (int a=0; a<COL; a++)
	{
        for (int k=0; k<=R; k++)
        {
            cf[a] += corout[a][k];
        }
	}
	for (int a=0; a<COL; a++)
        cout << "sum" << a+1  << "=" << cf[a] << endl;
    for (int a=0; a<COL; a++)
    {
        if (cf[a] != 0)
        {
            for (int l=0; l<=R; l++)
            {
                corout[a][l] /= cf[a];
            }
        }
    }

    //加入fai判断的正负值
    for (int j=0;j<=(R-2);j++)
    {
        if (sitaout[j]==sitaout[j+2])
        {
            for (int a=0;a<COL;a++)
            {
                corout[a][j] += corout[a][j+2];
            }
        }
    }
    /*for (int a=0;a<COL;a++)
    {
        corout[a][R-2] += corout[a][R];
    }*/

	//output
	ofstream fout;
	fout.open("Angles-fai.dat");
	fout << "sita 0 1 2 3 4..." << endl;
	for (int m=0; m<=R; m++)
	{
		cout << right << sitaout[m] << "\n";
		if ((m==0)||(m%3!=0))
        {
            fout.width(8);
		    fout << right << sitaout[m] << "\t";
            for (int a=0; a<COL; a++)
                 fout << corout[a][m] << "\t";
            fout << endl;
        }
	}
	fout.close();

	delete [] sita;
	delete [] fai;
	delete [] sitaout;
    for (int a=0; a<COL; a++)
        delete [] cor[a];
    delete [] cor;
    for (int a=0; a<COL; a++)
        delete [] corout[a];
    delete [] corout;
	return 0;
}
