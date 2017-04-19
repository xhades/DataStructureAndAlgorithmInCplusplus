import numpy as np
import pandas as pd
import matplotlib
matplotlib.rc('axes', edgecolor='white', facecolor='white')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D 

df = pd.read_csv('spatial data.txt', header=None)
spatial_data = df.as_matrix()
spatial_data -= 500

fig = plt.figure()  
ax = fig.add_subplot(111, projection='3d') 
ax.scatter(spatial_data[:, 0], spatial_data[:, 1], spatial_data[:, 2], s=5, c='r', depthshade=True)
ax.plot([-500, 500], [0, 0], [0, 0], 'k--')
ax.plot([0, 0], [-500, 500], [0, 0], 'k--')
ax.plot([0, 0], [0, 0], [-500, 500], 'k--')
ax.set_xlabel('x')
ax.yaxis.tick_top()
ax.set_xlim([-500, 500])
ax.set_xticks([])
ax.set_ylabel('y')
ax.set_ylim([500, -500])
ax.set_yticks([])
ax.set_zlabel('z')
ax.set_zlim([500, -500])
ax.set_zticks([])

plt.grid(False)
plt.show()
