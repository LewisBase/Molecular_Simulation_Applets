#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<string>
#include<cctype>
#include<cmath>

int main()
{
    using namespace std;
    string file;
    string null;
    double distance;
    double length = 9.0;

    ifstream fin;
    cin >> file;
    fin.open(file.c_str());
    if (!fin.is_open())
    {
        cerr << file << " could not be opened.\n";
        exit(EXIT_FAILURE);
    }
    while (fin >> null)
    {
        if (null == "xy")
            break;
    }
    fin >> null >> null >> null >> distance;
    if (distance < -0.5 )
    {
        distance += length;
    }
    cout << distance << endl;
    return 0;
}
