#用于批量计算不同体系不同粒径的界面张力
#在Result-Sphere文件夹下运行
#作者：lewisbase
#日期：2019.04.05

import csv
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import ticker
from matplotlib import rcParams

density=np.array(['1.4E-4','1.8E-4'])
name=np.array(['As2O3'])#,'C60','CdO','CrO3','CuO','FeO','NiO','PbO','SiO2','V2O5','ZnO'])
size=np.array(['1nm','1.5nm','2nm','2.5nm','3nm','3.5nm'])
S=2500                  #A^-3

###########################################################计算部分###########################################################
for i in name:
    with open('Tension-output.csv','a',newline='') as csvfile:
        Twriter=csv.writer(csvfile)
        Twriter.writerow([' ',i])
    for j in size:
        PATH0='{which_density}/{which_particle}/{what_size}'.format(which_density=density[0],which_particle=i,what_size=j)
        PATH1='{which_density}/{which_particle}/{what_size}'.format(which_density=density[1],which_particle=i,what_size=j)
        densityfile=np.array([PATH0+'/densz.dat',PATH1+'/densz.dat'])
        energyfile=np.array([PATH0+'/output.dat',PATH1+'/output.dat'])
        #print(densityfile)
        rhoz0=np.loadtxt(densityfile[0],dtype='float',usecols=(1),skiprows=10)
        rhoz1=np.loadtxt(densityfile[1],dtype='float',usecols=(1),skiprows=10)
        rho=np.array([np.max(rhoz0),np.max(rhoz1)])
        #print(rho[0],rho[1])
        energyf0=open(energyfile[0])
        energyf1=open(energyfile[1])
        energy=np.array([energyf0.readlines(),energyf1.readlines()])
        F=np.array([float(energy[0][-1][24:31]),float(energy[1][-1][24:31])])
        #print(F[0],F[1])
        energyf0.close()
        energyf1.close()
        Tension=2478/6.02*(F[0]*rho[1]-F[1]*rho[0])/(S*(rho[1]-rho[0]))
        #print(Tension)
        with open('Tension-output.csv','w',newline='') as csvfile:
            Twriter=csv.writer(csvfile)
            Twriter.writerow([j,Tension])

##############################################绘图部分##############################################################
linecolor=["black","red","blue","darkcyan","magenta","khaki","navy","mediumvioletred","pink","olive","lightskyblue"]
plt.figure(figsize=(15,12),dpi=100,frameon=True)
plt.xlabel('Particle Diameter (nm)',fontsize=40)
plt.ylabel('$\gamma$ (mN/m)',fontsize=40)
plt.xticks(fontsize=32)
plt.yticks(np.linspace(50,90,5),fontsize=32)
for num in range(np.size(name)):
    startnum=num+1
    xpD=np.array([1.0,1.5,2.0,2.5,3.0,3.5])
    ydT=np.loadtxt('Tension-output.csv',delimiter=',',usecols=startnum,skiprows=1)
    plt.plot(xpD,ydT,label=name[num],linewidth=3,color=linecolor[num],marker='o',ms=9)
    #plt.scatter(xpD,ydT,c=linecolor[num],linewidth=3)
plt.legend(loc='upper left',fontsize=26,frameon=False,ncol=2)
ax=plt.gca()
ax.spines['top'].set_linewidth(5)
ax.spines['right'].set_linewidth(5)
ax.spines['bottom'].set_linewidth(5)
ax.spines['left'].set_linewidth(5)
plt.tick_params(width=5,direction='in')

formatter=ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True)
formatter.set_powerlimits((-3,3))
ax.xaxis.set_major_formatter(formatter)
ax.yaxis.set_major_formatter(formatter)
rcParams.update({'font.size':30,'font.family':'serif'})

plt.savefig("Tension.png",dpi=300)
plt.show()