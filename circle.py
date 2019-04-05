#使用最小二乘法拟合圆方程
#作者：lewisbase
#日期：2019.03.18
import numpy as np
from scipy.optimize import leastsq
import matplotlib.pyplot as plt
import math


x,y=np.loadtxt('num.dat',delimiter=' ',dtype=float,usecols=(0,1),unpack=True)

#for i in x:
#    print i
#for j in y:
#    print j

plt.plot(x,y,color="red",label="origin",linewidth=2)

def residuals(p):
    a,b,r=p
    return r**2-(y-b)**2-(x-a)**2
	
result=leastsq(residuals,[1,1,1])
a,b,r=result[0]
print("a=",a,"b=",b,"r=",r)


yfit=np.sqrt(r**2-(x-a)**2)+b
plt.plot(x,yfit,"b--",label="fit",linewidth=2)
plt.legend(loc="upper right",frameon=False)
plt.annotate('(x-112.892403261)$^2$+(y+58.8238235027)$^2$=110.123575696$^2$',xy=(40,15))
plt.annotate('R=110.123575696',xy=(100,10))

plt.show()