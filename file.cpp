// file.cpp ---- 读取文件并删除无用行 
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>

using namespace std;

int main()
{
    string file;
	string filename;
    string null;
    cout << "Input the file name:  (Press Ctrl+C to quit)" << endl;
    while (cin >> file)
    {
		filename = file + ".txt";
    	cout << "File name is: " << filename << endl;
    	
    	ifstream fin(filename.c_str(), ios::in);
    	//ofstream fout("test.txt");
    	if (!fin.is_open())
    	{
    		cerr << filename << "could not be opened.\n";
    		exit(EXIT_FAILURE);
		}
    	while (fin >> null)
    	{
        	//cout << null << endl;
        	//fout << null << endl;
        	if (null == "Current/A")
        		break;
    	}

    	//fout.close();
    	double data[3200][2];
    	for (int i=0; i<3200; i++)
    	{
    		fin >> data[i][0] >> null >> data[i][1];
		}
		string fileout;
		fileout = file + "-new.txt";
		ofstream fout(fileout.c_str());
		for (int i=800; i<2401; i++)
		{
			fout << data[i][0] << "\t" << data[i][1] << endl;
		}
		fout.close();
		fin.close();
		cout << "Mission complete!" << endl;
		cout << "Input the file name (Press Ctrl+C to quit): " << endl;
	}

    return 0;
}
