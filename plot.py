import numpy as np
import matplotlib.pyplot as plt
from sys import exit

tv = 2e-3
tc = tv/4.
tr = 2.5e-2

msd = np.loadtxt("msd.dat")

t = msd[:,0]
x = msd[:,1]
y = msd[:,2]
z = msd[:,3]

plt.plot(t,x,label="x")
plt.plot(t,y,label="y")
plt.plot(t,z,label="z")

plt.axvline(tc,label='tc',color='blue')
plt.axvline(tv,label="tv",color='red')
plt.axvline(tr,label='tr',color='green')

plt.yscale('log')
plt.xscale('log')

plt.legend()
plt.show()

