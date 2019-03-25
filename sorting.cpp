#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<iomanip>
#include<cstdlib>

const int ROW = 199;
const int COL = 19;
using namespace std;

int main()
{
	double * sita = new double [1000];
	double ** cor = new double *[COL];
	for (int i=0;i<COL;i++)
	{
		cor[i] = new double [1000];
	}
	
	double sitatemp=0.0;
	double cortemp = 0.0;
	
	//read-in
	ifstream fin;
	fin.open("Angles-fai.dat",ios::in);
	if (!fin.is_open())
	{
		cerr << "Could open the file!" << endl;
		exit(EXIT_FAILURE);
	}
	
	for (int i=0;i<ROW;i++)
	{
		fin >> sita[i];
		if (sita[i] < 0)
		{
			sita[i] = -(180-(-sita[i]*180)/3.14);
		} else
		{
			sita[i] = 180-(sita[i]*180)/3.14;
		}
		for (int j=0;j<COL;j++)
			fin >> cor[j][i];
		cout << sita[i] << "\t";
		for (int j=0;j<COL;j++)
			cout << cor[j][i] << "\t";
		cout << endl;
	}
	fin.close();

	
	//sorting
	for (int i=0;i<ROW;i++)
	{
		for (int j=i+1;j<ROW;j++)
		{
			if (sita[i] > sita[j])
			{
				sitatemp = sita[i];
				sita[i] = sita[j];
				sita[j] = sitatemp;
				for (int k=0;k<COL;k++)
				{
					cortemp = cor[k][i];
					cor[k][i] = cor[k][j];
					cor[k][j] = cortemp;
				}
			}
		}
	}
	
	//output
	ofstream fout;
	fout.open("Angles-fai-sort.dat");
	for (int i=0;i<ROW;i++)
	{
		cout << sita[i] << "\t";
		fout.width(8);
		fout << right << sita[i] << "\t";
		for (int j=0;j<COL;j++)
		{
			fout << cor[j][i] << "\t";
			cout << cor[j][i] << "\t";
		}
		fout << endl;
		cout << endl;
	}
	fout.close();
	
	delete [] sita;
	for (int i=0;i<COL;i++)
		delete [] cor[i];
	delete [] cor;
	
	return 0;

	
}
