// 用于生成SDS尾链的ndx分组
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream Fileout;
	Fileout.open("tail.ndx");
	int a=6, i=0, n=0;
	Fileout << "[ SDS tail ]" << endl;
	for (i=0; i<512; i++)
	{
		for (int b=0; b<=36; b++)
		{
			Fileout << a << " ";
			a++;
			n++;
			if (n>=15 && n%15==0)
				Fileout << endl;
		}
		a+=5;
	}
	Fileout.close();
	return 0;
}
