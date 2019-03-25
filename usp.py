#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#用于绘制球体与单点之间的势能曲线


import numpy as np
import math
from pylab import *



R=10
PI=3.1415926


sigc1=4.24
epsc1=69.06085432
rhoc1=0.061540355
sigc2=4.3
epsc2=103.9289276
rhoc2=0.050407037
sigc3=3.925
epsc3=65.5902508
rhoc3=0.077071291


xnm=np.linspace(1,3,500)
x=10*xnm
y1=16*PI/3*rhoc1*R**3*epsc1*(((5*R**6+45*R**4*x**2+63*R**2*x**4+15*x**6)*sigc1**12)/(15*(x**2-R**2)**9)-sigc1**6/(3*(x**2-R**2)**3))
y2=16*PI/3*rhoc2*R**3*epsc2*(((5*R**6+45*R**4*x**2+63*R**2*x**4+15*x**6)*sigc2**12)/(15*(x**2-R**2)**9)-sigc2**6/(3*(x**2-R**2)**3))
y3=16*PI/3*rhoc3*R**3*epsc3*(((5*R**6+45*R**4*x**2+63*R**2*x**4+15*x**6)*sigc3**12)/(15*(x**2-R**2)**9)-sigc3**6/(3*(x**2-R**2)**3))

figure(figsize=(15,12),dpi=100)
xlabel("r (nm)",fontsize=40)
ylabel("u(r) (K)",fontsize=40)
xlim(1,3)
ylim(-150,200)
yticks(np.linspace(-100,200,4,endpoint=True),fontsize=32)
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
#savefig("LJ-sphere-R10.png",dpi=300)