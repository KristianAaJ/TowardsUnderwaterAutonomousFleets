import numpy as np
import pandas as pd

df1 = pd.read_csv("data1.csv")
df2 = pd.read_csv("data2.csv")

#print(df1['yaw_ref'], df1['psi'])
#
#print(df2['yaw_ref'][780:800])

dfa = df2[700:825]
dfb = df1[700:825]

firt_it = True
rot_count = 0

for i in range(780, 800):
    v = [dfb['x'][i]-dfa['x'][i], dfb['y'][i]-dfa['y'][i]]
    yaw = np.arctan2(v[1], v[0])
    
    if firt_it:
        yaw_old = yaw
        firt_it = False

    if yaw - yaw_old < -3:
        rot_count += 1
        
    elif yaw - yaw_old > 3:
        rot_count -= 1
        
    
    yaw_out = yaw + rot_count*2*np.pi #yaw_out is the correct yaw angle
    yaw_old = yaw
    
    print(str(i) + ': ' + str(yaw_out))
