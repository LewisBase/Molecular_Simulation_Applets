#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于绘制界面张力随颗粒物粒径变化规律曲线
#作者：lewisbase
#日期：2019.03.29


import numpy as np
import math
from pylab import *

NA=6.02e23


k=[10.4852,9.21986,10.80252,12.12507,11.71712,11.84442,11.62607,11.89865,11.20948,10.10373,9.88793]
b=[-6.17879,-5.36126,-6.74615,-7.33804,-7.03924,-7.279,-7.18832,-7.20815,-6.96632,-6.03662,-5.89056]
name=["As2O3","PbO","CdO","CrO3","CuO","FeO","NiO","V2O5","ZnO","SiO2","C60"]
linecolor=["black","red","blue","darkcyan","magenta","khaki","navy","mediumvioletred","pink","olive","lightskyblue"]
y=[]



x=np.linspace(1,10**4.2,5000)

for i in range(11):
    g=((k[i]*x+b[i])*1e6/NA)/(100)
    y.append(g)




figure(figsize=(15,12),dpi=100)
xlabel("D (nm)",fontsize=40)
ylabel("$\Delta$$\gamma$ (mN/m)",fontsize=40)
xlim(0,10**4.2)
ylim(0,3e-15)
yticks(np.linspace(0,3e-15,4,endpoint=True),fontsize=32)
xticks(np.linspace(1,10**4,5,endpoint=True),fontsize=32)

for i in range(11):
    plot(x,y[i],label=name[i],linewidth=3,color=linecolor[i])


legend(loc='upper left',fontsize=26,frameon=False)
ax=gca()
ax.spines['top'].set_linewidth(5)
ax.spines['bottom'].set_linewidth(5)
ax.spines['left'].set_linewidth(5)
ax.spines['right'].set_linewidth(5)
tick_params(top='off',right='off',width=5)

show()
#savefig("LJ-sphere-R10.png",dpi=300)