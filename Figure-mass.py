#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于计算不同PM2.5颗粒物在肺泡中沉积的分布函数与造成界面张力的变化
#作者：lewisbase
#日期：2019.03.28

#from __future__ import division
import numpy as np
import math
import matplotlib.pylab as plt
from matplotlib import ticker
from matplotlib import rcParams
from scipy import integrate

#from sympy import *

GRID=5000               #计算中的分格点数
NUM=11                  #总计算的颗粒数
NA=6.02e23              #阿伏伽德罗常数

k=[10.4852,9.21986,10.80252,12.12507,11.71712                           #自由能拟合经验参数k
  ,11.84442,11.62607,11.89865,11.20948,10.10373
  ,9.88793]
b=[-6.17879,-5.36126,-6.74615,-7.33804,-7.03924                         #自由能拟合经验参数b
  ,-7.279,-7.18832,-7.20815,-6.96632,-6.03662
  ,-5.89056]
rhov=[61.540355,50.407037,77.071291,67.985298,100.125156                #体积密度nm^-3
      ,98.400984,110.497238,78.784468,84.031848,65.377281
      ,86.703667]
rhom=[6.57807E-23,1.85216E-22,1.06312E-22,4.15282E-23,6.64452E-23       #质量密度g/atom
      ,5.98007E-23,6.22924E-23,4.31894E-23,6.72757E-23,3.32226E-23
      ,1.99336E-23]
name=["As2O3","PbO","CdO","CrO3","CuO","FeO","NiO","V2O5","ZnO","SiO2","C60"]
linecolor=["black","red","blue","darkcyan","magenta","khaki","navy","mediumvioletred","pink","olive","lightskyblue"]
y=np.array([])                                  #粒径按质量的分布函数
rho=np.array([])                                #总密度g/nm^3
D=np.linspace(1,10**4.2,GRID)                   #粒径
mD=np.array([])                                 #粒径对应的质量
dg=np.array([])                                 #界面张力变化量
fid=np.array([])                                #归一化求和

for i in range(NUM):
    buff=rhov[i]*rhom[i]
    rho=np.append(rho,buff)


for i in range(NUM):
    mDbuff=4/3*math.pi*(D/2)**3*rho[i]
    mD=np.append(mD,mDbuff)
mD=mD.reshape(NUM,GRID)

def distribution(md):
    return -0.03049+0.181629*math.exp(-1.63563*(-3.16382+math.log10((6*md/(math.pi*rhod))**(1/3)))**2) \
            +0.538395*math.exp(-1.88135*(-1.23534+math.log10((6*md/(math.pi*rhod))**(1/3)))**2)

for i in range(NUM):
    fidbuff=0
    for m in mD[i,:]:
        rhod=rho[i]
        fidbuff=fidbuff+distribution(m)
    fid=np.append(fid,fidbuff)

tid=np.array([])
for i in range(NUM):
    tidbuff=0
    for m in mD[i,:]:
        rhod=rho[i]
        tidbuff=tidbuff+distribution(m)/fid[i]
    tid=np.append(tid,tidbuff)
print (tid)
    
for i in range(NUM):
    for m in mD[i,:]:
        rhod=rho[i]
        ybuff=distribution(m)
        y=np.append(y,ybuff/fid[i])
        dgbuff=((k[i]*(6*m/(math.pi*rho[i]))**(1/3)+b[i])*1e6/NA)/100
        dg=np.append(dg,dgbuff)
    
dg=dg.reshape(NUM,GRID)
y=y.reshape(NUM,GRID)

plt.figure(figsize=(15,15),dpi=100)
      
plt.xlabel("Mass (g)",fontsize=40)
plt.ylabel("Probability",fontsize=40)
plt.xlim(-0.5e-10,1e-9)
plt.ylim(0,2e-3)
plt.yticks(np.linspace(0,2e-3,5,endpoint=True),fontsize=32)
plt.xticks(fontsize=32)

for i in range(NUM):
    plt.plot(mD[i,:],y[i,:],label=name[i],linewidth=3,color=linecolor[i])

plt.legend(loc='upper right',fontsize=26,frameon=False,ncol=2)
ax1=plt.gca()
ax1.spines['top'].set_linewidth(5)
ax1.spines['bottom'].set_linewidth(5)
ax1.spines['left'].set_linewidth(5)
ax1.spines['right'].set_linewidth(5)
plt.tick_params(top='off',right='off',width=5,direction='in')

formatterx = ticker.ScalarFormatter(useMathText=True)
formatterx.set_scientific(True) 
formatterx.set_powerlimits((-1,1)) 
ax1.xaxis.set_major_formatter(formatterx)
formattery = ticker.ScalarFormatter(useMathText=True)
formattery.set_scientific(True) 
formattery.set_powerlimits((-1,1)) 
ax1.yaxis.set_major_formatter(formattery)
rcParams.update({'font.size': 30, 'font.family': 'serif'})#设置左上角标签大小

plt.savefig('Probability.png',dpi=300)



plt.figure(figsize=(15,15),dpi=100)
plt.xlabel("Mass (g)",fontsize=40)
plt.ylabel("$\Delta$$\gamma$ (mN/m)",fontsize=40)
plt.xlim(0,1e-9)
plt.ylim(-3e-16,3e-15)
plt.yticks(np.linspace(0,3e-15,5,endpoint=True),fontsize=32)
plt.xticks(fontsize=32)

for i in range(11):
    plt.plot(mD[i,:],dg[i,:],label=name[i],linewidth=3,color=linecolor[i])

plt.legend(loc='upper right',fontsize=26,frameon=False,ncol=2)
ax2=plt.gca()
ax2.spines['top'].set_linewidth(5)
ax2.spines['bottom'].set_linewidth(5)
ax2.spines['left'].set_linewidth(5)
ax2.spines['right'].set_linewidth(5)
plt.tick_params(top='off',right='off',width=5,direction='in')

formatter = ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True) 
formatter.set_powerlimits((-1,1)) 
ax2.yaxis.set_major_formatter(formatter)
ax2.xaxis.set_major_formatter(formatter)
rcParams.update({'font.size': 30, 'font.family': 'serif'})#设置左上角标签大小

plt.savefig('dTension.png',dpi=300)

plt.show()
