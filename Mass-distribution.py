#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于绘制PM2.5颗粒物在肺泡内沉积粒径分布——转换为质量的形式
#作者：lewisbase
#日期：2019.03.28

#from __future__ import division
import numpy as np
import math
import matplotlib.pylab as plt
from matplotlib import ticker
from matplotlib import rcParams

GRID=5000               #计算中的分格点数

rhov=[61.540355         #体积密度nm^-3
,50.407037
,77.071291
,67.985298
,100.125156
,98.400984
,110.497238
,78.784468
,84.031848
,65.377281
,86.703667
]
rhom=[6.57807E-23       #质量密度g/atom
,1.85216E-22
,1.06312E-22
,4.15282E-23
,6.64452E-23
,5.98007E-23
,6.22924E-23
,4.31894E-23
,6.72757E-23
,3.32226E-23
,1.99336E-23
]
name=["As2O3","PbO","CdO","CrO3","CuO","FeO","NiO","V2O5","ZnO","SiO2","C60"]
linecolor=["black","red","blue","darkcyan","magenta","khaki","navy","mediumvioletred","pink","olive","lightskyblue"]
y=np.array([])                                  #粒径按质量的分布函数
rho=np.array([])                                #总密度g/nm^3

for i in range(11):
    buff=rhov[i]*rhom[i]
    rho=np.append(rho,buff)

D=np.linspace(1,10**4.2,GRID)      #粒径
mD=np.array([])                    #粒径对应的质量
for i in range(11):
    mDbuff=4/3*math.pi*(D/2)**3*rho[i]
    mD=np.append(mD,mDbuff)
mD=mD.reshape(11,GRID)

for i in range(11):
    for m in mD[i,:]:
        ybuff=-0.0000320101+0.000565238*math.exp(-0.0394272*(6.74167-math.log10(m/(rho[i]*math.pi)))**2)+0.000190684*math.exp(-0.0342777*(20.0631-math.log10(m/(rho[i]*math.pi)))**2)
        y=np.append(y,ybuff)

y=y.reshape(11,GRID)
#print y
plt.figure(figsize=(15,12),dpi=100)
plt.xlabel("Mass (g)",fontsize=40)
plt.ylabel("Probability",fontsize=40)
plt.xlim(0,1e-9)
plt.ylim(2.2e-4,6e-4)
plt.yticks(np.linspace(2e-4,6e-4,5,endpoint=True),fontsize=32)
plt.xticks(fontsize=32)

for i in range(11):
    plt.plot(mD[i,:],y[i,:],label=name[i],linewidth=3,color=linecolor[i])

plt.legend(loc='upper right',fontsize=26,frameon=False)
ax=plt.gca()
ax.spines['top'].set_linewidth(5)
ax.spines['bottom'].set_linewidth(5)
ax.spines['left'].set_linewidth(5)
ax.spines['right'].set_linewidth(5)
plt.tick_params(top='off',right='off',width=5,direction='in')
formatterx = ticker.ScalarFormatter(useMathText=True)
formatterx.set_scientific(True) 
formatterx.set_powerlimits((-1,1)) 
ax.xaxis.set_major_formatter(formatterx)
ax.yaxis.set_major_formatter(formatterx)
rcParams.update({'font.size': 30, 'font.family': 'serif'})#设置左上角标签大小

plt.show()
