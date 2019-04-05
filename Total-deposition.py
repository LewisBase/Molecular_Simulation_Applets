#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于计算不同PM2.5颗粒物在肺泡中的总沉积造成界面张力的变化
#作者：lewisbase
#日期：2019.03.28

from __future__ import division
import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib import ticker
from scipy import integrate
from matplotlib import rcParams

GRID=10000               #计算中的分格点数
NUM=11                  #总计算的颗粒数
NA=6.02e23              #阿伏伽德罗常数

k=[10.4852,9.21986,10.80252,12.12507,11.71712                           #自由能拟合经验参数k
  ,11.84442,11.62607,11.89865,11.20948,10.10373
  ,9.88793]
b=[-6.17879,-5.36126,-6.74615,-7.33804,-7.03924                         #自由能拟合经验参数b
  ,-7.279,-7.18832,-7.20815,-6.96632,-6.03662
  ,-5.89056]
rhov=[61.540355,50.407037,77.071291,67.985298,100.125156                #体积密度atom/nm^3
      ,98.400984,110.497238,78.784468,84.031848,65.377281
      ,86.703667]
rhom=[6.57807E-23,1.85216E-22,1.06312E-22,4.15282E-23,6.64452E-23       #质量密度g/atom
      ,5.98007E-23,6.22924E-23,4.31894E-23,6.72757E-23,3.32226E-23
      ,1.99336E-23]
name=["As2O3","PbO","CdO","CrO3","CuO","FeO","NiO","V2O5","ZnO","SiO2","C60"]
linecolor=["black","red","blue","darkcyan","magenta","khaki","navy","mediumvioletred","pink","olive","lightskyblue"]
D=np.linspace(1,10**4.2,GRID)                            #粒径
rho=np.zeros([NUM])                                      #总密度g/nm^3
mD=np.zeros([NUM,GRID])                                  #粒径对应的质量
fid=np.zeros([NUM])                                      #归一化因子
tD=np.zeros([NUM])                                       #总沉积量


#####################################################定义函数###########################################################################
def distribution(md):                                    #分布函数
    return -0.03049 \
           +0.181629*math.exp(-1.63563*(-3.16382+math.log10((6*md/(math.pi*rhod))**(1/3)))**2) \
           +0.538395*math.exp(-1.88135*(-1.23534+math.log10((6*md/(math.pi*rhod))**(1/3)))**2)

def area(md):
    return 70.0                                                #肺泡总面积
    #return math.pi*(6*md/(math.pi*rhod))**(2/3)*1e-18         #颗粒打开的面积

def deposition(md):                                     #总张力计算函数
    return distribution(md) \
            *(kd*(6*md/(math.pi*rhod))**(1/3)+bd)*1e6 \
            /(md*NA*area(md))                                              #P(m)*dr(m)/(m*Area*alvnum)

#####################################################计算部分###########################################################################
for i in range(NUM):                                    #计算密度g/nm^3
    rho[i]=rhov[i]*rhom[i]

for i in range(NUM):                                    #计算颗粒质量g
    for j in range(GRID):
        mD[i][j]=4/3*math.pi*(D[j]/2)**3*rho[i]

for i in range(NUM):                                    #对分布函数归一化，一为/sum()方法，一为/integrate()方法
    rhod=rho[i]
    for j in range(GRID):
        fid[i]+=distribution(mD[i][j])
    #fidbuff=integrate.quad(distribution,1/6*math.pi*rhod,1/6*math.pi*rhod*10**12.6)
    #fid[i]=fidbuff[0]
print ("fid: \n")
print (fid)

for i in range(NUM):                                    #计算总界面张力影响，一为sum()方法，一为integrate()方法
    rhod=rho[i]
    kd=k[i]
    bd=b[i]
    for j in range(GRID):
        tD[i]+=deposition(mD[i][j])/fid[i]
    #td=integrate.quad(deposition,1/6*math.pi*rhod,1/6*math.pi*rhod*10**12.6)
    #tD[i]=td[0]/fid[i]

print ("tD: \n")
print (tD)

#####################################################绘图部分##########################################################################
plt.figure(figsize=(15,15),dpi=100)
plt.xlabel("Deposition Mass (g)",fontsize=40)
plt.ylabel("Total $\Delta$$\gamma$ (mN/m)",fontsize=40)
plt.xlim(0,1e-8)
#plt.ylim(-1e7,1.8e8)
plt.yticks(fontsize=32)
plt.xticks(fontsize=32)     #np.linspace(1e-9,1e-8,5,endpoint=True),

for i in range(NUM):
    x=np.linspace(0,1e-8,10000)
    y=tD[i]*x
    plt.plot(x,y,label=name[i],linewidth=3,color=linecolor[i])

plt.legend(loc='upper left',fontsize=26,frameon=False,ncol=2)
ax=plt.gca()
ax.spines['top'].set_linewidth(5)
ax.spines['bottom'].set_linewidth(5)
ax.spines['left'].set_linewidth(5)
ax.spines['right'].set_linewidth(5)
plt.tick_params(top='off',right='off',width=5,direction='in')

formatter = ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True) 
formatter.set_powerlimits((-1,1)) 
ax.yaxis.set_major_formatter(formatter)
ax.xaxis.set_major_formatter(formatter)
rcParams.update({'font.size': 30, 'font.family': 'serif'})#设置左上角标签大小

plt.savefig('TotaldTension-TotalArea.png',dpi=300)
#plt.show()


