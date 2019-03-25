#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>

using namespace std;

const double r = 0;				 // 水阻尼系数
const double TOF = 1.0e-6;				 // 迭代容差
double acceleration(const double &, const double &, const double &, const double &);
double velocity(const double &, const double &, const double &);
double distance(const double &, const double &, const double &);


int main()
{
	double v0 = 0;				// 初始速度
	cin >> v0;
	ofstream pout("output.dat", ios::out | ios::app);
    pout << "v0 = " << v0 << endl;
	pout.close();
	// 批量文件读入与输出
	char input[20];					      // 视文件数目决定
	for (int file = 0; file < 33; file++)  // 同上
	{
		string tip;					      // 无效信息
		string molname;				      // 穿越分子名称
		double M = 0.0; 				  // 穿越分子摩尔质量
		int Num = 0;				      // 坐标点总数
		
		double * xi = new double [1000];	  // 反应坐标点
		double * Fi = new double [1000];   // 自由能
		double * fi = new double [1000];   // 计算力
		double * ai = new double [1000];   // 加速度
		double * vi = new double [1000];   // 速度


		
		sprintf(input,"energy%d.dat",file);
		ifstream fin(input, ios::in);
		// 读入能量坐标 
		fin >> molname;
		cout << "Molcule's Name: " << molname << endl;
		fin >> M;
		M /= 6.02e26;
		cout << "Molar Mass: " << M << endl;
		fin >> Num;
		cout << "Coordinate Numbers: " << Num << endl;
		cout << "Coordinate" << "\t" << "Free Energy" << endl;
		int i = 0;
		string null;
		for (i = 0; i < Num; i++)
		{
			fin >> xi[i] >> Fi[i];
            xi[i] *= 1.0e-9;
            Fi[i] *= 4.11e-21;
			cout << xi[i] << "\t" << Fi[i] << endl;
		}
		fin.close();
		
		// 求计算参数
		cout << endl << "fi" << endl;
		for (i = 0; i < (Num-1); i++)
		{
			fi[i] = -(Fi[i+1]-Fi[i])/(xi[i+1]-xi[i]);	// 计算fi
			cout << i << "\t" << fi[i] << endl;
		}
		
		
		// 牛顿第二定律计算速度变化
		cout << "v0 = " << v0 << endl << endl;
		vi[0] = v0;													// 初始速度
		double dt = 1e-14;											// 步长
		double xt = 0.0;											// 最终位置
		double vt = 0.0;											// 最终速度
		double d = 0.0;												// 距离判断
		for (i = 0; i < Num; i++)
		{
			cout << "------------------STEP " << i << " ------------------" << endl;
			while (d<(xi[i+1]-xi[i]))
			{
				ai[i] = acceleration(fi[i], r, M, vi[i]);
				vi[i] = velocity(ai[i],vi[i],dt);
				if (vi[i] < 0)
					break;
				d += distance(ai[i],vi[i],dt);
				vt = vi[i];
				cout << molname << " step " << i << " Distance d = " << d << " Velocity v = " << vi[i] << endl;
			}
			if (vi[i] < 0)
			{
				cout << "velocity decrease less than zero! vt = " << vi[i] << endl;
				break;
			}
			vi[i+1] = vi[i];
			xt += d;
			if (xt > (xi[(Num-1)]-xi[0]))
			{
				cout << "molecule can transport through surfactant! xt = " << xt << endl;
				cout << "step : " << i << endl;
				break;
			}
			d = 0.0;
			cout << "distance xt = " << xt << " velocity vi = " << vi[i] << endl;
		}
		
		ofstream fout("output.dat", ios::out | ios::app);
        fout << "molname" << "\t" << "xt" << "\t" << "vt" << "\t" << "step" << endl;
		fout << molname << "\t" << xt << "\t" << vt << "\t" << i << endl;
		fout.close();
		
		delete [] xi;
		delete [] Fi;
		delete [] fi;
		delete [] ai;
		delete [] vi;

	}
	ofstream fout("output.dat", ios::out | ios::app);
    fout << endl;
	fout.close();
	return 0;
}

double acceleration(const double & FI, const double & R, const double & MA, const double & Vi)
{
	double AI = 0.0;
	AI = (FI - R * Vi) / MA;
	return AI;
}

double velocity(const double & Ai, const double & Vi, const double & DT)
{
	double vik2 = 0.0;
	vik2 = Vi + Ai * DT;
	return vik2;
}

double distance(const double & Ai, const double & Vi, const double & DT)
{
	double d = 0.0;
	d = Vi * DT + 1/2 * Ai * DT * DT;
	return d;
}
