// 分子模拟课程作业ppt4，第一题
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

const int MAXN = 100;
const double kT1 = 0.3;
const double kT2 = 0.15;


int main(){

int step=0;
double average=0,variance=0;
double sum[10000];
for (int i=0;i<10000;i++)
	sum[i]=0;
srand((unsigned)time(NULL));

while (step<10000){
	int box[MAXN][MAXN];
	int x,y;
	int n=0;
	double energy=0.0;
	
	for (int i=0;i<MAXN;i++){
		for (int j=0;j<MAXN;j++)
			box[i][j]=0;
	}

	while (n<((MAXN*MAXN)/2)){
		x=rand()%MAXN;
		y=rand()%MAXN;
		if (box[x][y] == 0){
			box[x][y] =1;
			n++;
			//cout << box[x][y] << "\t" << n << endl;
		}
	}
	int num = 0;
	for (int i=0;i<MAXN;i++){
		for (int j=0;j<MAXN;j++){
			cout << box[i][j] << " ";
			num++;
			if (num%MAXN==0)
				cout << endl;
		}
	}
	cout << endl << "Martix complete!" << endl;
	
	for (int i=0;i<MAXN;i++){
		for (int j=0;j<MAXN;j++){
			if (i==0 || j==0 || i==(MAXN-1) || j==(MAXN-1)){
				if (box[i][j]==1)
					energy += kT2;
			} 
			if (i!=(MAXN-1) && j!=(MAXN-1)){
				if (box[i][j]==1 && box[i+1][j]==1){
					energy += kT1;
				}
				if (box[i][j]==1 && box[i][j+1]==1){
					energy += kT1;
				}
			}
			if (i==(MAXN-1)){
				if (box[i][j]==1 && box[i][j+1]==1){
					energy += kT1;
				}
			}
			if (j==(MAXN-1)){
				if (box[i][j]==1 && box[i+1][j]==1){
					energy += kT1;
				}
			}
		}
	}
	sum[step] = energy;
	energy = 0;
	cout << "Step: " << step+1 << "\t" << "Energy: " << sum[step] << endl << endl;
	step++;
}

for (int i=0;i<step;i++){
	average += sum[i];
}
average = average/step;
for (int i=0; i<step;i++){
	variance += ((sum[i]-average)*(sum[i]-average));
}
variance = sqrt(variance/step);
cout << "The average of the energy is: " << average << endl;
cout << "The variance of the energy is: " << variance << endl;

string null;
cin >> null; 
return 0;
}
