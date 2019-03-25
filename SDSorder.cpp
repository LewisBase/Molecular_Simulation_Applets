// SDS-C472体系SDS尾链序参量索引生成
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream fout;
	fout.open("SDS72order.ndx");
	int a = 31;
	for (int i = 0; i < 36; i++)
	{
		fout << "[ a" << i+1 << " ]" << endl;
		fout << a << endl;
		fout << "[ b" << i+1 << " ]" << endl;
		fout << a+1 << endl;
		fout << "[ c" << i+1 << " ]" << endl;
		fout << a+11 << endl;
		a += 67;
	}
	fout.close();
	return 0;
}
