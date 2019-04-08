import numpy as np
import matplotlib.pyplot as plt
from sys import exit

msd = np.loadtxt("msd.dat")

t = msd[:,0]
x = msd[:,1]
y = msd[:,2]
z = msd[:,3]

plt.scatter(t,x,label="x",color='blue')
plt.scatter(t,y,label="y",color='red')
plt.scatter(t,z,label="z",color='green')

plt.xscale("log")
plt.yscale("log")

plt.xlim([0.9*t[0],1.1*t[-1]])
plt.ylim([1e-12,1e5])

plt.legend()
plt.tight_layout()
plt.show()
