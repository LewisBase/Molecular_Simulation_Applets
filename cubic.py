from __future__ import division
import numpy as np
from scipy import integrate
from scipy.optimize import leastsq
from pylab import *

#Cubic length width hight A
A=10
B=10
C=10

#Average sigma(s,A) epsilon(e,K) rho(r,A^-3)
#As2O3 
s=np.array([4.24,3.84]); e=np.array([208.4541197,69.0609]); r=0.061540355
#CdO s=np.array([3.925,3.525]); e=np.array([197.9784079,65.5903]); r=0.077071291
#CrO3 s=np.array([4.0375,3.6375]); e=np.array([115.1869133,38.1614]); r=0.067985298
#CuO s=np.array([4.1,3.7]); e=np.array([94.04972089,31.1587]); r=0.100125156
#FeO s=np.array([3.95,3.55]); e=np.array([99.63608784,33.0094]); r=0.098400984
#NiO s=np.array([3.925,3.525]); e=np.array([100.9844047,33.4561]); r=0.110497238
#PbO s=np.array([4.3,3.9]); e=np.array([313.7003347,103.929]); r=0.050407037
#V2O5 s=np.array([4.04285714,3.6428571]); e=np.array([113.6077211,3706382]); r=0.078784468
#ZnO s=np.array([3.925,3.525]); e=np.array([158.2665473,52.4337]); r=0.084031848

#filename
file=open('LJ.dat','w')

def LJ_cubic(x,y,z):
	return 4*eps*rho*((sig**2/((xb-x)**2+(yb-y)**2+(zb-z)**2))**6-(sig**2/((xb-x)**2+(yb-y)**2+(zb-z)**2))**3)

lx=50
ly=50
lz=100
dx=lx/101
dy=ly/101
dz=lz/201
#count=0
x0=lx/2-A/2
x1=lx/2+A/2
y0=ly/2-B/2
y1=ly/2+B/2
z0=lz/2-C/2
z1=lz/2+C/2
for m in np.linspace(0,1,2):	
    for ix in np.linspace(0,100,101):
        for iy in np.linspace(0,100,101):
            for iz in np.linspace(0,200,201):
                xb=ix*dx
                yb=iy*dy
                zb=iz*dz
                sig=s[m]
                eps=e[m]
                rho=r
                if abs(xb-lx/2)<(A/2) and abs(yb-ly/2)<(B/2) and abs(zb-lz/2)<(C/2) :
                    LJ = 1E100
                else:
                    LJ=integrate.tplquad(LJ_cubic,
                        z0,
                        z1,
                        lambda y: y0,
                        lambda y: y1,
                        lambda y,x: x0,
                        lambda y,x: x1)
                LJ=LJ[0]/298.15
                file.write(str(xb)+'\t')
                file.write(str(yb)+'\t')
                file.write(str(zb)+'\t')
                file.write(str(LJ)+'\n')
                print "%f    %f    %f    %f\n"%(xb,yb,zb,LJ)
                #count+=1
                #if count%10==0:
                #    file.write('\n')

file.close()
                                

