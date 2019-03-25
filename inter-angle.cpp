#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<cctype>

using namespace std;

const int ROWIN=2000;
const int ROWOUT=100;

int main()
{
	// input message
	double * sita = new double [2000];
	double * fai = new double [2000];
	double * cor1 = new double [2000];
	double * cor2 = new double [2000];
	double * cor3 = new double [2000];
	string tip;
	int R = 0;

	//output message
	double * sitaout = new double [2000];
	double * cor1out = new double [2000];
	double * cor2out = new double [2000];
	double * cor3out = new double [2000];

	//normalizing
	double cf1=0.0, cf2=0.0, cf3=0.0;

	//read-in
	ifstream fin;
	fin.open("Angles.dat",ios::in);
	if (!fin.is_open())
	{
		cerr << "Could not open the file!" << endl;
		exit(EXIT_FAILURE);
	}
	fin >> tip >> tip >> tip >> tip >> tip;
	cout << "Read in file data!" << endl << "sita fai 0 1 2" << endl;
	for (int i=0; i<ROWIN; i++)
	{
		fin >> sita[i] >> fai[i] >> cor1[i] >> cor2[i] >> cor3[i];
		cout.width(4);
		//cout << setiosflags(ios::fixed) << setprecision(8);	// scientific notation
		cout << right << sita[i] << "\t" << fai[i] << "\t" << cor1[i] << "\t"
			<< cor2[i] << "\t" << cor3[i] << endl;
	}
	fin.close();

	/*//test
	double cf11=0,cf21=0,cf31=0;
	for (int k=0; k<ROWIN; k++)
	{
		cf11 += cor1[k];
		cf21 += cor2[k];
		cf31 += cor3[k];
	}
	cout << "cf11=" << cf11 << endl << "cf21=" << cf21 << endl << "cf31=" << cf31 << endl;*/

	//intergrate
	for (int j=0; j<(ROWIN-1); j++)
	{
		if (sita[j] == sita[j+1])
		{
			//cout << "sita[" << j << "]=sita[" << j+1 << "]=" << sita[j] << endl;
			cor1[j+1] += cor1[j];
			cor2[j+1] += cor2[j];
			cor3[j+1] += cor3[j];
		}
		else
		{
			sitaout[R] = sita[j];
			cor1out[R] = cor1[j];
			cor2out[R] = cor2[j];
			cor3out[R] = cor3[j];
			R++;
		}
	}
	cout << "R=" << R << endl;
	sitaout[R] = sita[1999];
	cor1out[R] += cor1[1999];
	cor2out[R] += cor2[1999];
	cor3out[R] += cor3[1999];

	// normalize

	for (int k=0; k<ROWOUT; k++)
	{
		cf1 += cor1out[k];
		cf2 += cor2out[k];
		cf3 += cor3out[k];
	}
	cout << "cf1=" << cf1 << endl << "cf2=" << cf2 << endl << "cf3=" << cf3 << endl;
	if (cf1 != 0)
	{
		for (int l=0; l<ROWOUT; l++)
		{
			cor1out[l] /= cf1;
		}
	}
	if (cf2 != 0)
	{
		for (int l=0; l<ROWOUT; l++)
		{
			cor2out[l] /= cf2;
		}
	}
	if (cf3 != 0)
	{
		for (int l=0; l<ROWOUT; l++)
		{
			cor3out[l] /= cf3;
		}
	}


	//output
	ofstream fout;
	fout.open("Angles-integrate.dat");
	fout << "sita 0 1 2" << endl;
	for (int m=0; m<ROWOUT; m++)
	{
		fout.width(8);
		//fout.setf(ios::fixed);
		fout << right << sitaout[m] << "\t" << cor1out[m] << "\t" << cor2out[m]
			<< "\t" << cor3out[m] << endl;
	}
	fout.close();

	delete [] sita;
	delete [] fai;
	delete [] cor1;
	delete [] cor2;
	delete [] cor3;
	delete [] sitaout;
	delete [] cor1out;
	delete [] cor2out;
	delete [] cor3out;

	return 0;
}
