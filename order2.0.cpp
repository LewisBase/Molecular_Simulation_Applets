// order.cpp -- make index file of SDS and C4m to calculate order parameter
/* 
变量名称规则：
	FirstSC             表示第一个SDS分子尾链上首个C的序号;
	SDSlen              表示SDS分子的原子总数;
	C4mLen              表示C4m分子的原子总数;
	SDStailLen          表示SDS尾链的原子数;
	SDSheadLen          表示SDS头基的原子数;
	C4mtailLenC         表示C4m尾链上非氢原子数;
	C4mtailLenH         表示C4m尾链上氢原子数;
	C4mheadLenC         表示C4m头基上非氢原子数;
	C4mheadLenH         表示C4m头基上氢原子数;
	SDStop/bot.         分别表示上下两层的分子数;
	SCt/SCb             分别表示上下两层SDS尾链首个C的序号;
	CCht/CHht/CChb/CHhb 分别表示上下两层C4m头基首个C或H的序号;
	CCtt/CHtt/CCtb/CHtb 分别表示上下两层C4m尾链首个首个C或H的序号;
*/

#include<iostream>
#include<fstream>

const int FirstSC = 6;
const int SDSLen = 42;
const int C4mLen = 25;
const int SDStailLen = 37;
const int SDSheadLen = 5;
const int C4mtailLenC = 4;
const int C4mtailLenH = 9;
const int C4mheadLenC = 6;
const int C4mheadLenH = 6;
const int SDStailLenC = 12;

int main()
{
	using namespace std;
	int SDStop, SDSbot, C4mtop, C4mbot;
	cout << "输入上层SDS分子个数：" << endl;
	cin >> SDStop;
	cout << "输入上层C4m分子个数：" << endl;
	cin >> C4mtop;
	cout << "输入下层SDS分子个数：" << endl;
	cin >> SDSbot;
	cout << "输入下层C4m分子个数：" << endl;
	cin >> C4mbot;

// SDS 序参量信息
	ofstream fout;
	fout.open("SDSorder.ndx");
	int SCt, SCb;
	SCt = FirstSC;
	SCb = SCt + SDSLen * SDStop + C4mLen * C4mtop;
	int n = 0, num = 0;
	for (int i = 0; i < SDStailLenC; i++)
	{
		fout << endl << "[ C" << num + 1 << " ]" << endl;	
		for(int j = 0; j < SDStop; j++)
		{
			
			fout.width(4);
			fout << right << SCt << " ";
			SCt += (SDSLen + C4mLen);// 跳到下一分子同位置的碳
			n++;
			if (n % 15 == 0)
				fout << endl;
		}
		SCt -= (SDSLen * SDStop + C4mLen * C4mtop - 1);// 回到起始位置并向前移动1
		for (int j = 0; j < SDSbot; j++)
		{
			fout.width(4);
			fout << right << SCb << " ";
			SCb += SDSLen;
			n++;
			if (n % 15 == 0)
				fout << endl;
		}
		SCb -= (SDSLen * SDSbot - 1); 
		num++;
		n = 0;
	}
	fout.close();
	cout << "CHECK! The total number of SDS is: " << n/SDStailLenC << endl;

// C4m 序参量信息
	fout.open("C4morder.ndx");
	int CCt, CCb;
	CCt = FirstSC + SDStailLen + C4mheadLenC;;
	CCb = CCt + SDSLen * (SDStop + SDSbot - 1) + C4mLen * C4mtop;
	n = 0;
	num = 0;
	for (int i = 0; i < C4mtailLenC; i++)
	{
		fout << endl << "[ C" << num + 1 << " ]" << endl;
		for (int j = 0; j < C4mtop; j++)
		{
			fout.width(4);
			fout << right << CCt << " " ;
			CCt += (C4mLen + SDSLen);
			n++;
			if (n % 15 == 0)
				fout << endl;
		}
		CCt -= (C4mLen * C4mtop + SDSLen * SDStop  - 1);
		for (int j = 0; j < C4mbot; j++)
		{
			fout.width(4);
			fout << right << CCb << " ";
			CCb += C4mLen;
			n++;
			if (n % 15 == 0)
				fout << endl;
		}
		CCb -= (C4mLen * C4mbot - 1);
		num++;
		n = 0;
	}
	fout.close();
	cout << "CHECK! The total number of C4m is: " << n/C4mtailLenC << endl;

	return 0;
}
