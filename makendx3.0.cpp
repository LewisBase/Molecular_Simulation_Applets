// makendx3.0.cpp -- make index file of middle
/*
变量名称规则:
FirstDA             DPPC上首个原子序号
DPPClen             DPPC分子的原子总数
AZOlen              AZO分子的原子总数
DPPCtop/bot         DPPC上下两层的分子数
AZOtop/bot          AZO上下两层的分子数
DPPCht/DPPChb       DPPC上下两层的头基原子序号
AZOht/AZOhb         AZO上下两层的头基原子序号
*/

#include<iostream>
#include<fstream>

const int FirstDA = 4601;
const int DPPClen = 12;
const int AZOlen = 13;

int main()
{
    using namespace std;

    int DPPCtop, DPPCbot, AZOtop, AZObot;
    cout << "输入单层DPPC分子个数： " << endl;
    cin >> DPPCtop;
    cout << "输入单层AZO分子个数： " << endl;
    cin >> AZOtop;

    ofstream fout;
    fout.open("indexs.ndx", ios_base::in | ios_base::app);

// 写入上层界面上的原子团信息
    int DPPCht=0, AZOht=0;
    DPPCht = FirstDA;
    AZOht = DPPCht + DPPClen * DPPCtop + AZOlen - 3;
    fout << endl << "[ Upinterface ]" << endl;
    int n = 0;

    for (int i = 0; i < DPPCtop; i++){
        for (int j = 0; j < 1; j++){
            fout.width(4);
            fout << right << DPPCht << " ";
            DPPCht++;
            n++;
            if (n % 15 == 0)
                fout << endl;
        }
            DPPCht += (DPPClen-1);
     }
    for (int i = 0; i < AZOtop; i++){
        for (int j = 0; j < 1; j++){
            fout.width(4);
            fout << right << AZOht << " ";
            AZOht++;
            n++;
            if (n % 15 == 0)
                fout << endl;
        }
        AZOht += (AZOlen - 1);
    }

//下层数据暂不需要

    fout.close();
    return 0;
}
