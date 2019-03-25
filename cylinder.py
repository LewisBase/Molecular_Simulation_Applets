import numpy as np
from scipy import integrate
from scipy.optimize import leastsq
from pylab import *

#Cylinder Radiu A
R=25
#Cylinder Hight A
H=20.0
#Average sigma
#As2O3 s=3.84
#CdO s=3.525
#CrO3 s=3.6375
#CuO s=3.7
#FeO s=3.55
#NiO s=3.525
#PbO s=3.9
#V2O5 s=3.6428571
#ZnO s=3.525

def LJ_cylinder(c,r,z):
	return r*((s**2/(x**2+r**2-2*r*x*np.cos(c)+z**2+z0**2-2*z*z0))**6-(s**2/(x**2+r**2-2*r*x*np.cos(c)+z**2+z0**2-2*z*z0))**3)

list=[]
for x in np.linspace(27.5,29.5,200):
    for z0 in np.linspace(-5,25,200):
        y=integrate.tplquad(LJ_cylinder,
            0.0,
            H,
            lambda z: 0.0,
            lambda z: R,
            lambda z,r: 0.0,
            lambda z,r: 2*np.pi)
        print y[0]
        list.append(y[0])

xt=np.linspace(27.5,29.5,200)
yt=np.array(list)
xlabel("x(A)")
ylabel("u(r)")
xlim(27.5,29.5)
ylim(-30,10)
plot(xt,yt)
show()

#def residuals(p):
#	a,b=p
#	return yt-a/xt**12+b/xt**6
#	
#result=leastsq(residuals,[1,1])
#a,b=result[0]
#print "a=",a,"b=",b
