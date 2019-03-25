#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于绘制圆柱体与单点之间的势能曲线


import numpy as np
import math
from pylab import *



R=10
H=20
PI=3.1415926


sigc1=4.24
epsc1=69.06085432
rhoc1=0.061540355
sigcfit1=12.78
epscfit1=12.01


sigc2=4.3
epsc2=103.9289276
rhoc2=0.050407037
sigcfit2=12.81
epscfit2=12.54


sigc3=3.925
epsc3=65.5902508
rhoc3=0.077071291
sigcfit3=12.54
epscfit3=9.49



xnm=np.linspace(1,3,500)
x=10*xnm
y1=16*epsc1*rhoc1*epscfit1*((sigcfit1/x)**12-(sigcfit1/x)**6)
y2=16*epsc2*rhoc2*epscfit2*((sigcfit2/x)**12-(sigcfit2/x)**6)
y3=16*epsc3*rhoc3*epscfit3*((sigcfit3/x)**12-(sigcfit3/x)**6)

figure(figsize=(15,12),dpi=100)
xlabel("r (nm)",fontsize=40)
ylabel("u(r) (K)",fontsize=40)
xlim(1,3)
ylim(-350,200)
yticks(np.linspace(-300,200,6,endpoint=True),fontsize=32)
xticks(fontsize=32)

plot(xnm,y1,label="As2O3",linewidth=3)
plot(xnm,y2,label="PbO",linewidth=3)
plot(xnm,y3,label="CdO",linewidth=3)
legend(loc='upper right',fontsize=26,frameon=False)
ax=gca()
ax.spines['top'].set_linewidth(5)
ax.spines['bottom'].set_linewidth(5)
ax.spines['left'].set_linewidth(5)
ax.spines['right'].set_linewidth(5)
tick_params(top='off',right='off',width=5)

show()
#savefig("LJ-cylinder-R10.png",dpi=1080)
