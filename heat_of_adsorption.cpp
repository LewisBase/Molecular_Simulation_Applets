//Calcultie heat of adsorption through Langmuir function and C-C function
//Author: lewisbase
//Date: 2019.03.28

#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;
const int grid1 = 20000;
const double rangeP1 = 120.0;
const int grid2 = 50000;
const double rangeP2 = 240.0;
const double R = 8.314510e-3;

int main()
{
    double T1=273.0,T2=298.0;       // parameters in Langmuir function
    double Qm1=3.4295,Qm2=2.28922;
    double B1=0.01199,B2=0.00459;
    double t1=1.12095,t2=1.24069;
    
    cout << "Input the parameter of the first line: " << endl;
    cout << "T1 = " << endl;
    cin >> T1;
    cout << T1 << endl << "Qm1 = " << endl;
    cin >> Qm1;
    cout << Qm1 << endl << "B1 = " << endl;
    cin >> B1;
    cout << B1 << endl << "t1 = " << endl;
    cin >> t1;
	cout << t1 << endl;
    
    cout << "Input the parameter of the second line: " << endl;
    cout << "T2 = " << endl;
    cin >> T2;
    cout << T2 << endl << "Qm2 = " << endl;
    cin >> Qm2;
    cout << Qm2 << endl << "B2 = " << endl;
    cin >> B2;
    cout << B2 << endl << "t2 = " << endl;
    cin >> t2;
	cout << t2 << endl;
    
    
    double Q1[grid1];        // function Q-P
    double Q2[grid2];
    double P1[grid1];
    double P2[grid2];
    
    for (int i=0; i<grid1; i++)
    {
        P1[i]=rangeP1/grid1*i;
        Q1[i]=Qm1*pow(B1,1/t1)*P1[i]/pow((1+B1*P1[i]),1/t1);
        cout.width(8);
        cout << i << " P1: " << P1[i] << " Q1: " << Q1[i] << endl;
    }
    for (int i=0; i<grid2; i++)
    {
        P2[i]=rangeP2/grid2*i;
        Q2[i]=Qm2*pow(B2,1/t2)*P2[i]/pow((1+B2*P2[i]),1/t2);
        cout.width(8);
        cout << i << " P2: " << P2[i] << " Q2: " << Q2[i] << endl;
    }
    
    double * DP = new double[grid1];        // parameter in C-C function
    double * DH = new double[grid1];
    double * Qfin = new double[grid1];
    double DT = 1/T2-1/T1;
    cout << DT << endl;
    int length = 0;                         // record the length of the DP and Qfin
    for (int i=0; i<grid1; i++)
    {
        for (int j=0; j<grid2; j++)
        {
        	//cout << i << " " << j << " in cycle\n";
            if (abs(Q1[i]-Q2[j])<1E-06&&P2[j]!=0)
            {
                DP[length]=P1[i]/P2[j];
                cout << "DP: " << DP[length] << endl;
                Qfin[length]=Q1[i];
                cout << "Q1: "<< Q1[i] << " Q2: "<< Q2[j] << " Qfin: " << Qfin[length] << endl;
                length++;
                continue;
            }
        }
    }
    
    ofstream fout;
    fout.open("Q-DH.dat",ios::out); 
    for (int i=0; i<length; i++)
    {
        DH[i]=R*log(DP[i])/DT;
        cout.width(8);
        cout << "Q: " << Qfin[i] << " DH: " << DH[i] << endl;
        fout << Qfin[i] << "\t" << DH[i] << endl;
    }
    fout.close();
    
    
    delete [] DP;
    delete [] DH;
    delete [] Qfin;
    return 0;
    
}
