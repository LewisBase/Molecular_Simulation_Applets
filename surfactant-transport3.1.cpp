#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>

using namespace std;

const double r = 5.82e-14;				 // 空气阻尼系数
const double TOF = 1.0e-6;				 // 迭代容差
double v0 = 110;				// 初始速度

double velocity(const double &, const double &, const double &, const double &, const double &, const double &);
double determine(const double &, const double &, const double &, const double &);

int main()
{
	ofstream pout("output.dat", ios::out | ios::app);
    pout << "v0 = " << v0 << endl;
	pout.close();
	// 批量文件读入与输出
	char input[15];					      // 视文件数目决定
	for (int file = 0; file < 9; file++)  // 同上
	{
		string tip;					      // 无效信息
		string molname;				      // 穿越分子名称
		double M = 0.0; 				  // 穿越分子摩尔质量
		int Num = 0;				      // 坐标点总数
		
		double * xi = new double [1000];	  // 反应坐标点
		double * Fi = new double [1000];   // 自由能
		double * ai = new double [1000];   // 计算参数
		double b = 0.0;					  // 计算参数
		double * vi = new double [1000];   // 速度
		double * xj = new double [1000];   // 速度方向判定方法

		
		sprintf(input,"energy%d.dat",file);
		ifstream fin(input, ios::in);
		// 读入能量坐标 
		fin >> molname >> tip >> tip >> tip;
		cout << "Molcule's Name: " << molname << endl;
		fin >> M;
		M /= 6.02e26;
		cout << "Molar Mass: " << M << endl;
		fin >> Num;
		cout << "Coordinate Numbers: " << Num << endl;
		cout << "Coordinate" << "\t" << "Free Energy" << endl;
		int i = 0;
		for (i = 0; i < Num; i++)
		{
			fin >> xi[i] >> tip >> Fi[i] >> tip >> tip;
            xi[i] *= 1.0e-9;
            Fi[i] *= 4.11e-21;
			cout << xi[i] << "\t" << Fi[i] << endl;
		}
		fin.close();
		
		// 求计算参数
		cout << endl << "ai" << endl;
		//ai[0] = 0.0;
		for (i = 0; i < (Num-1); i++)
		{
			ai[i] = -(1/r)*(Fi[i+1]-Fi[i])/(xi[i+1]-xi[i]);	// 计算ai
			cout << i << "\t" << ai[i] << endl;
		}
		
	    cout << endl << "b" << endl;
		b = M/r;											// 计算b
		cout << b << endl;
		
		// 牛顿迭代计算速度变化
		//v0 = sqrt(2.0*4.11e-21/M);
		cout << "v0 = " << v0 << endl << endl;
		vi[0] = v0;													// 初始速度
		double vo = v0-10.0;										// 迭代预估值
		double xt = 3.0;											// 最终位置
		double vt = 3.0;											// 最终速度
		for (i = 1; i < Num; i++)
		{
			vi[i] = velocity(xi[i], xi[i-1], ai[i-1], b, vi[i-1], vo);
			xj[i] = determine(xi[i], ai[i], b, vi[i]);
			if (i<30)
			{
				/*if (xj[i] <= xi[i+1])
				{
					xt = xi[i];
					vt = vi[i];
					cout << "Cannot reach next coordinate" << endl;
					cout << "The coordinate where velocity reduced less than zero: " << xi[i] << endl;
					cout << "The velocity: " << vi[i] << endl << endl << endl;
					break;
				}*/
				if (vi[i] <= 0)
				{
					xt = xi[i];
					vt = vi[i];
					cout << "velocity reduced less than zero" << endl;
					cout << "The coordinate where velocity reduced less than zero: " << xi[i] << endl;
					cout << "The velocity: " << vi[i] << endl << endl << endl;
					break;
				}
			}
            vo = (vo + vi[i])/2;
		}
		
		ofstream fout("output.dat", ios::out | ios::app);
        fout << "molname" << "\t" << "xt" << "\t" << "vt" << endl;
		fout << molname << "\t" << xt << "\t" << vt << endl;
		fout.close();
		
		delete [] xi;
		delete [] Fi;
		delete [] ai;
		delete [] vi;
		delete [] xj;
	}
	ofstream fout("output.dat", ios::out | ios::app);
    fout << endl;
	fout.close();
	return 0;
}
			

double velocity(const double & Xi, const double & Xj, const double & Ai, const double & B, 
	const double & Vj, const double & Vo)
{
	double vik1 = Vo;
	double vik2 = 0.0;

	if (((Ai-vik1)/(Ai-Vj)) > 0)
	{
		cout << ">0" << endl;
		vik2 = vik1+(Xi-Xj+Ai*B*log(fabs((Ai-vik1)/(Ai-Vj)))-B*(Vj-vik1))*(Ai-vik1)/(B*vik1);
	} else if (((Ai-vik1)/(Ai-Vj)) < 0)
	{
		cout << "<0" << endl;
		vik2 = vik1-(Xi-Xj+Ai*B*log(fabs((Ai-vik1)/(Ai-Vj)))-B*(2*Ai-Vj-vik1))*(vik1-Ai)/(B*vik1);
	} else
	{
		cout << "log equal to zero!" << endl;
		return vik2;
	}
	if (vik2 <= 0)
	{
		cout << "!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
			<< "velocity decreased less than zero!" << endl;
		return vik2;
	}
	cout << "----------------------------" << "Step" << "--------------------------" << endl;
	cout << "vik2 = " << vik2 << endl;
	while (fabs(vik2-vik1) > TOF)
	{
		vik1 = vik2;
		//if (vik1 <= 0 || ((Ai-vik1)/(Ai-Vj)) <= 0)
		//	break;
		if (((Ai-vik1)/(Ai-Vj)) > 0)
		{
			cout << ">0" << endl;
			vik2 = vik1+(Xi-Xj+Ai*B*log(fabs((Ai-vik1)/(Ai-Vj)))-B*(Vj-vik1))*(Ai-vik1)/(B*vik1);
		} else if (((Ai-vik1)/(Ai-Vj)) < 0)
		{
			cout << "<0" << endl;
			vik2 = vik1-(Xi-Xj+Ai*B*log(fabs((Ai-vik1)/(Ai-Vj)))-B*(2*Ai-Vj-vik1))*(vik1-Ai)/(B*vik1);
		} else
		{
			cout << "log equal to zero!" << endl;
			break;
		}
		if (vik2 <= 0)
			break;
		cout << "TOF = " << fabs(vik2-vik1) << endl;
		cout << "vik2 = " << vik2 << "\t" << "vik1 = " << vik1 << "\t" << "xi+1 = " << Xi
			<< "\t" << "xi = " << Xj << "\t" << "ai = " << Ai << "\t" << "b = " << B << "\t"
			<< "vi = " << Vj << endl << endl;
	}
	return vik2;
}

double determine(const double & Xi, const double & Ai, const double & B, const double & Vi)
{
	double x = 0.0;
	if (Ai == 0)
		x = Xi+B*Vi;
	else
		x = Xi-Ai*B*log(fabs(Ai/(Ai-Vi)))+B*Vi;
	cout << "determine x = " << x << endl << endl;
	return x;
}
			
